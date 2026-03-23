#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>
#include <QDateTime>
#include <QScreen>
#include <QUuid>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeComponent();
    setupTreeData();
    connect(ui->deviceWidget, &QTableWidget::customContextMenuRequested,this, &MainWindow::onTableContextMenu);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int windowWidth = this->width();
    int windowHeight = this->height();

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;
    this->move(x, y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeComponent()
{
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 9);
}

void MainWindow::setupTreeData()
{
    rootTreeView = new TreeView(ui->treeView, this);

    QIcon icon1 = qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation); 
    QIcon icon2 = qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical);    
    QIcon icon3 = qApp->style()->standardIcon(QStyle::SP_DirIcon);               

    rootTreeView->addNode("标准测试用例", "标准测试用例", static_cast<int>(DeviceTest::NodeType::TestCategory), QVariant(), nullptr, QIcon(":/icons/standard.png"));
    rootTreeView->addNode("测试任务存档", "测试任务存档", static_cast<int>(DeviceTest::NodeType::TestCategory), QVariant(), nullptr, QIcon(":/icons/database.png"));
    rootTreeView->addNode("当前测试任务", "当前测试任务", static_cast<int>(DeviceTest::NodeType::TestCategory), QVariant(), nullptr, QIcon(":/icons/task.png"));
    connect(rootTreeView, &TreeView::contextMenuRequested, this, &MainWindow::onTreeContextMenu);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::onTreeItemClicked);
}

void MainWindow::onTreeContextMenu(const QPoint &pos, const QString &key)
{
    if (key.isEmpty()) return;

    QStandardItem *item = rootTreeView->findNodeByKey(key);
    if (!item) return;

    int typeValue = item->data(Qt::UserRole + 2).toInt(); 
    NodeType type = static_cast<NodeType>(typeValue);

    QMenu menu(this);

    switch (type) {
        case NodeType::TestCategory: {
            // 创建二级菜单
            QMenu *subMenuNew = menu.addMenu(QIcon(":/icons/add.png"), "新建(N)"); 
            addMenuAction(subMenuNew, "新建厂家设备分类(C)", TreeAction::AddChild, QIcon(":/icons/folder.h"));
            
            menu.addSeparator();
            addMenuAction(&menu, "导入脚本(L)", TreeAction::ImportScd, QIcon(":/icons/import.png"));
            break;
        }

        case NodeType::VendorDevice: 
            addMenuAction(&menu, "新增测试集", TreeAction::AddChild);
            addMenuAction(&menu, "删除分类", TreeAction::Delete, QIcon(":/icons/delete.png"));
            break;

        case NodeType::TestItem: 
            addMenuAction(&menu, "立即执行测试", TreeAction::RunTest, QIcon(":/icons/run.png"));
            addMenuAction(&menu, "查看历史报告", TreeAction::ViewReport);
            menu.addSeparator();
            addMenuAction(&menu, "删除测试项", TreeAction::Delete);
            break;

        default: 
            addMenuAction(&menu, "添加子项", TreeAction::AddChild);
            addMenuAction(&menu, "删除", TreeAction::Delete);
            break;
    }

    // 使用全局坐标弹出
    QAction *selected = menu.exec(ui->treeView->viewport()->mapToGlobal(pos));
    
    if (selected) {
        TreeAction action = static_cast<TreeAction>(selected->data().toInt());
        handleTreeAction(action, key);
    }
}

void MainWindow::onTreeItemClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    int typeValue = index.data(Qt::UserRole + 2).toInt();
    ui->stackedWidget->setCurrentIndex(typeValue);
}

void MainWindow::onTableContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->deviceWidget->indexAt(pos);
    QMenu menu(this);
    if (index.isValid()) {
        QAction *importScdAct = menu.addAction("导入SCD");
        connect(importScdAct, &QAction::triggered, this, &MainWindow::onImportScdRequested);

    }
    menu.exec(ui->deviceWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::onImportScdRequested()
{

}

QAction* MainWindow::addMenuAction(QMenu *parent, const QString &text, TreeAction actionType, const QIcon &icon) {
    QAction *act = parent->addAction(icon, text);
    act->setData(static_cast<int>(actionType)); 
    return act;
}

void MainWindow::handleTreeAction(TreeAction action, const QString &key) {
    if (action == TreeAction::AddChild) {

        QStandardItem* parentItem = rootTreeView->findNodeByKey(key);
        if (!parentItem) return;

        int currentType = parentItem->data(Qt::UserRole + 2).toInt();

        if (currentType >= static_cast<int>(NodeType::TestItem)) {
            qDebug() << "已达到最大层级，无法添加子节点";
            return;
        }

        int childTypeInt = currentType + 1;
        NodeType childType = static_cast<NodeType>(childTypeInt);
        
        QIcon icon;
        QString title, label, defaultName;
        switch (childType) {
            case NodeType::VendorDevice: {
                title = "新建厂家"; 
                label = "厂家名称:";
                defaultName = "新厂家分类";
                icon = QIcon(":/icons/VendorDevice.png"); 
                break;
            }
            case NodeType::TestSet:{
                title = "新建测试集"; 
                label = "测试集名称:"; 
                defaultName = "新终端测试集";
                icon = QIcon(":/icons/TestSet.png");
                break;
            }   
            case NodeType::TestProject:{
                title = "新建项目"; 
                label = "项目名称:"; 
                defaultName = "新测试项目"; 
                icon = QIcon(":/icons/TestProject.png");
                break;
            }  
            case NodeType::TestGroup:{
                title = "新建分组"; 
                label = "分组名称:";
                defaultName = "新测试组";
                icon = QIcon(":/icons/TestGroup.png");
                break;
            }    
            case NodeType::TestItem:{
                title = "新建测试项";
                label = "项名称:"; 
                defaultName = "新测试项"; 
                icon = QIcon(":/icons/TestItem.png");
                break;
            }     
            default: {
                title = "新建节点"; 
                label = "名称:"; 
                defaultName = "未命名"; 
                qApp->style()->standardIcon(QStyle::SP_CustomBase);
                break;
            }                    
        }

        bool ok;
        QString name = QInputDialog::getText(this, title, label, QLineEdit::Normal, defaultName, &ok);
        if (!ok || name.trimmed().isEmpty()) return;
        QString newKey = QUuid::createUuid().toString(QUuid::WithoutBraces);
        rootTreeView->addNodeByKey(name, newKey, key, childTypeInt, QVariant(), icon);
        ui->treeView->expand(parentItem->index());
    }
}

void MainWindow::ImportScd()
{

}
