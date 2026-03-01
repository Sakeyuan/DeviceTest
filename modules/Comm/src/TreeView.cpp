#include <Comm/TreeView.h>

TreeView::TreeView(QTreeView *view, QObject *parent)
    : QObject(parent), m_treeView(view)
{
    if (!m_treeView)
        return;

    m_model = new QStandardItemModel(m_treeView);
    m_treeView->setModel(m_model);

    m_treeView->setHeaderHidden(true);
    m_treeView->setAnimated(true);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setIndentation(5);

    m_treeView->setStyleSheet(R"(
        QTreeView {
            background-color: #2b2b2b;      /* 暗色背景 */
            border: none;
            outline: 0;
            color: #dcdcdc;                 /* 文字颜色 */
        }
        QTreeView::item {
            padding: 0px;                   /* 增加行高，不那么拥挤 */
            border-radius: 2px;
        }
        QTreeView::item:hover {
            background-color: #3e3e42;      /* 悬停效果 */
        }
        QTreeView::item:selected {
            background-color: #094771;      /* 选中效果 */
            color: white;
        }
        /* 展开/收起按钮美化 (可以使用标准图标或自定义图片) */
        QTreeView::branch:has-children:!has-siblings:closed,
        QTreeView::branch:closed:has-children:has-siblings {
            image: url(:/icons/branch_closed.png); /* 替换为你的图标路径 */
        }
        QTreeView::branch:open:has-children:!has-siblings,
        QTreeView::branch:open:has-children:has-siblings  {
            image: url(:/icons/branch_open.png);
        }
    )");
    setEditable(false);
    connect(m_treeView, &QTreeView::customContextMenuRequested,
            this, &TreeView::onCustomContextMenuRequested);
}

QStandardItem *TreeView::addNode(const QString &text, const QString &key, QStandardItem *parent, const QIcon &icon)
{
    QStandardItem *item = new QStandardItem(text);
    if (!icon.isNull())
        item->setIcon(icon);

    // 存入 UserRole 并加入快速索引表
    if (!key.isEmpty())
    {
        item->setData(key, Qt::UserRole + 1);
        m_keyMap.insert(key, item);
    }

    if (parent)
    {
        parent->appendRow(item);
    }
    else
    {
        m_model->appendRow(item);
    }
    return item;
}

QStandardItem *TreeView::addNodeByKey(const QString &text, const QString &newKey,
                                      const QString &parentKey, const QIcon &icon)
{
    QStandardItem *parentItem = findNodeByKey(parentKey);
    return addNode(text, newKey, parentItem, icon);
}

QStandardItem *TreeView::findNodeByKey(const QString &key)
{
    return m_keyMap.value(key, nullptr);
}

void TreeView::removeSelected()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid())
        return;

    QStandardItem *item = m_model->itemFromIndex(index);
    if (item)
    {
        recursiveCleanupMap(item);

        if (item->parent())
        {
            item->parent()->removeRow(item->row());
        }
        else
        {
            m_model->removeRow(item->row());
        }
    }
}

void TreeView::recursiveCleanupMap(QStandardItem *item)
{
    if (!item)
        return;
    for (int i = 0; i < item->rowCount(); ++i)
    {
        recursiveCleanupMap(item->child(i));
    }
    QString key = item->data(Qt::UserRole + 1).toString();
    if (!key.isEmpty())
        m_keyMap.remove(key);
}

QString TreeView::getSelectedKey() const
{
    QModelIndex index = m_treeView->currentIndex();
    return index.isValid() ? index.data(Qt::UserRole + 1).toString() : QString();
}

void TreeView::setEditable(bool editable)
{
    m_treeView->setEditTriggers(editable ? QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed
                                         : QAbstractItemView::NoEditTriggers);
}

void TreeView::clear()
{
    m_model->clear();
    m_keyMap.clear();
}

void TreeView::expandAll() { m_treeView->expandAll(); }

void TreeView::onCustomContextMenuRequested(const QPoint &pos)
{

    QModelIndex index = m_treeView->indexAt(pos);

    QString key = index.isValid() ? index.data(Qt::UserRole + 1).toString() : QString();

    emit contextMenuRequested(pos, key);
}
