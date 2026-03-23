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
    m_treeView->setIndentation(10); 
    m_treeView->setRootIsDecorated(true);

   m_treeView->setStyleSheet(R"(
    /* 1. 整体背景：纯白背景配合深色文字 */
    QTreeView {
        background-color: #ffffff;
        border: none;
        outline: 0;
        color: #333333;                /* 深灰色文字，比纯黑更柔和 */
        font-family: "Segoe UI", "Microsoft YaHei";
        font-size: 13px;
    }

    /* 2. 节点行：增加高度，去掉生硬的分割线 */
    QTreeView::item {
        padding: 0px 5px 5px 0px;             /* 适当的内边距 */
        border: 1px solid transparent; /* 预留边框位置防止抖动 */
    }

    /* 3. 悬停与选中：使用柔和的浅蓝色 */
    QTreeView::item:hover {
        background-color: #f2f7ff;    /* 极浅蓝悬停 */
        color: #000000;
    }

    QTreeView::item:selected {
        background-color: #e5f0ff;    /* 浅蓝色选中 */
        color: #0056b3;                /* 选中文字变蓝 */
        font-weight: bold;             /* 选中字体加粗 */
    }

    QTreeView::item:selected:active {
        background-color: #d1e5ff;    /* 激活状态稍深 */
    }

    QScrollBar:vertical {
        background: #f1f1f1;
        width: 8px;
        margin: 0px;
    }
    QScrollBar::handle:vertical {
        background: #cccccc;
        min-height: 20px;
        border-radius: 4px;
    }
    QScrollBar::handle:vertical:hover {
        background: #bbbbbb;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        height: 0px;
    }
)");
    setEditable(false);
    connect(m_treeView, &QTreeView::customContextMenuRequested,
            this, &TreeView::onCustomContextMenuRequested);
}

QStandardItem *TreeView::addNode(const QString &text, const QString &key, int type, 
                                 const QVariant &userData, QStandardItem *parent, const QIcon &icon)
{
    QStandardItem *item = new QStandardItem(icon, text);
    item->setData(key, ROLE_KEY);
    item->setData(type, ROLE_TYPE);
    item->setData(userData, ROLE_DATA); 

    if (parent) parent->appendRow(item);
    else m_model->appendRow(item);

    if (!key.isEmpty()) m_keyMap[key] = item;
    return item;
}

QStandardItem *TreeView::addNodeByKey(const QString &text, 
                                      const QString &newKey,
                                      const QString &parentKey, 
                                      int type,               
                                      const QVariant &userData, 
                                      const QIcon &icon)
{
    QStandardItem *parentItem = findNodeByKey(parentKey);
    if (!parentKey.isEmpty() && !parentItem) {
        qWarning() << "TreeView: 找不到父节点 Key =" << parentKey << "，节点将添加至根部。";
    }
    return addNode(text, newKey, type, userData, parentItem, icon);
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
