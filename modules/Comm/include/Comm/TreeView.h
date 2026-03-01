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

    // 核心接口：添加节点，支持设置一个唯一 ID (Key) 方便查找
    QStandardItem *addNode(const QString &text,
                           const QString &key = QString(),
                           QStandardItem *parent = nullptr,
                           const QIcon &icon = QIcon());
    // TreeView.h 中
    // 重载 addNode，方便直接通过父节点的 key 添加子节点
    QStandardItem *addNodeByKey(const QString &text, const QString &newKey,
                                const QString &parentKey, const QIcon &icon = QIcon());
    // 功能接口
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
};

#endif