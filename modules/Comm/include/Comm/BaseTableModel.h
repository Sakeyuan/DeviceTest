#ifndef BASETABLEMODEL_H
#define BASETABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QVariant>
#include <functional>

template <typename T>
class BaseTableModel : public QAbstractTableModel {
public:
    // 定义列结构
    struct Column {
        QString header;
        std::function<QVariant(const T&)> getter;
        std::function<void(T&, const QVariant&)> setter;
    };

    // 修复 1: 确保构造函数是 public
    explicit BaseTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    // 修复 2: 显式处理指针和计数，增加内置过滤逻辑
    void setConfig(T *data, int count, const QList<Column> &columns) {
        beginResetModel();
        m_data = data;
        m_columns = columns;
        m_visibleRows.clear();

        for (int i = 0; i < count; ++i) {
            // 这里直接根据业务逻辑过滤（不显示 PRS7399）
            if (m_data[i].name && strstr(m_data[i].name, "PRS7399")) continue;
            m_visibleRows.append(i);
        }
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : m_visibleRows.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : m_columns.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= m_visibleRows.size()) return QVariant();

        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            int actualRow = m_visibleRows[index.row()];
            return m_columns[index.column()].getter(m_data[actualRow]);
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return m_columns.value(section).header;
        }
        return QVariant();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        if (!index.isValid()) return Qt::NoItemFlags;
        Qt::ItemFlags f = QAbstractTableModel::flags(index);
        if (m_columns[index.column()].setter) f |= Qt::ItemIsEditable;
        return f;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override {
        if (index.isValid() && role == Qt::EditRole && m_data) {
            int actualRow = m_visibleRows[index.row()];
            auto &column = m_columns[index.column()];
            if (column.setter) {
                column.setter(m_data[actualRow], value);
                emit dataChanged(index, index, {role});
                return true;
            }
        }
        return false;
    }

private:
    T *m_data = nullptr;
    QList<int> m_visibleRows;
    QList<Column> m_columns;
};

// 修复 3: 专门处理 C 风格 char 数组的辅助函数
template<typename T, typename ValueType>
typename BaseTableModel<T>::Column makeColumn(const QString& header, ValueType T::*member) {
    return typename BaseTableModel<T>::Column {
        header,
        [member](const T& obj) -> QVariant {
            // 处理 char 数组转 QVariant 的问题
            if constexpr (std::is_array_v<ValueType>) {
                return QVariant(static_cast<const char*>(obj.*member));
            } else {
                return QVariant::fromValue(obj.*member);
            }
        },
        [member](T& obj, const QVariant& val) {
            if constexpr (std::is_array_v<ValueType>) {
                // 处理写入 char 数组
                QString s = val.toString();
                strncpy((char*)(obj.*member), s.toLocal8Bit().data(), sizeof(obj.*member) - 1);
            } else {
                obj.*member = val.value<ValueType>();
            }
        }
    };
}

#endif // BASETABLEMODEL_H
