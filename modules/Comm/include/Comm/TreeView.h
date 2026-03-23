#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QObject>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <QIcon>
#include <QStyleFactory>

class TreeView : public QObject
{
    Q_OBJECT
public:
    explicit TreeView(QTreeView *view, QObject *parent = nullptr);

    QStandardItem *addNode(const QString &text, 
                                    const QString &key,
                                    int type, 
                                    const QVariant &userData, 
                                    QStandardItem *parent, 
                                    const QIcon &icon);

    QStandardItem *addNodeByKey(const QString &text, 
                                      const QString &newKey,
                                      const QString &parentKey, 
                                      int type = -1,               
                                      const QVariant &userData =  QVariant(), 
                                      const QIcon &icon = QIcon());
                                      
    void removeSelected();                            // 删除选中
    void recursiveCleanupMap(QStandardItem *item);    // 递归清理 KeyMap 中的节点
    void clear();                                     // 清空树
    QStandardItem *findNodeByKey(const QString &key); // 根据 Key 找节点 (C# 习惯)

    // 获取当前选中节点的属性
    QString getSelectedText() const;
    QString getSelectedKey() const;

    // 常用属性设置
    void setEditable(bool editable);
    void expandAll();



signals:
    void contextMenuRequested(const QPoint &pos, const QString &key);

private slots:
    void onCustomContextMenuRequested(const QPoint &pos);

private:
    QTreeView *m_treeView;
    QStandardItemModel *m_model;
    QMap<QString, QStandardItem *> m_keyMap;

    enum {
        ROLE_KEY = Qt::UserRole + 1,
        ROLE_TYPE = Qt::UserRole + 2,
        ROLE_DATA = Qt::UserRole + 3 
    };
};

#endif