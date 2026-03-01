#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QDateTime>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeComponent();
    setupTreeData();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int windowWidth = this->width();
    int windowHeight = this->height();

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    // 4. 移动窗体
    this->move(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeComponent()
{
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 9);
}

void MainWindow::setupTreeData()
{
    rootTreeView = new TreeView(ui->treeView, this);
    rootTreeView->addNode("根节点1", "root1", nullptr, qApp->style()->standardIcon(QStyle::SP_DirIcon));
    QIcon childIcon = qApp->style()->standardIcon(QStyle::SP_FileIcon);
    connect(rootTreeView, &TreeView::contextMenuRequested, this, [=](const QPoint &pos, const QString &key)
            {
                if (key.isEmpty()) return;

                QMenu menu(this);
                QAction *addChildAct = menu.addAction("添加子节点");

                // 执行菜单
                QAction *selected = menu.exec(ui->treeView->viewport()->mapToGlobal(pos));

                if (selected == addChildAct) {
                    // 弹出输入框获取新节点名称（Qt 标准对话框）
                    bool ok;
                    QString text = QInputDialog::getText(this, "添加子节点", "请输入节点名称:",
                                                         QLineEdit::Normal, "新子节点", &ok);

                    if (ok && !text.isEmpty()) {
                        // 生成一个唯一的 key（实际项目中可以用 UUID 或数据库 ID）
                        QString newKey = QString("%1_%2").arg(key).arg(QDateTime::currentMSecsSinceEpoch());

                        // 调用管理器添加节点
                        rootTreeView->addNodeByKey(text, newKey, key, childIcon);

                        // 自动展开父节点，以便看到新加的子节点
                        QStandardItem* parentItem = rootTreeView->findNodeByKey(key);
                        if (parentItem) {
                            ui->treeView->expand(parentItem->index());
                        }
                    }
                } });
}
