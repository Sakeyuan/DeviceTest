#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>
#include <QDateTime>
#include <QScreen>
#include <QUuid>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidget>
#include <QSortFilterProxyModel>

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

    ui->deviceTableView->setContextMenuPolicy(Qt::CustomContextMenu);
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
            // MENU
            QMenu *subMenuNew = menu.addMenu(QIcon(":/icons/add.png"), "MENU(N)"); 
            addMenuAction(subMenuNew, "新建(C)", TreeAction::AddChild, QIcon(":/icons/folder.h"));
            
            menu.addSeparator();
            addMenuAction(&menu, "MENU(L)", TreeAction::ImportScd, QIcon(":/icons/import.png"));
            break;
        }

        case NodeType::VendorDevice: 
            addMenuAction(&menu, "新建测试集", TreeAction::AddChild);
            addMenuAction(&menu, "Delete Category", TreeAction::Delete, QIcon(":/icons/delete.png"));
            break;

        case NodeType::TestItem: 
            addMenuAction(&menu, "Run Test Now", TreeAction::RunTest, QIcon(":/icons/run.png"));
            addMenuAction(&menu, "View History", TreeAction::ViewReport);
            menu.addSeparator();
            addMenuAction(&menu, "Delete Test Item", TreeAction::Delete);
            break;

        default: 
            addMenuAction(&menu, "Add Child Item", TreeAction::AddChild);
            addMenuAction(&menu, "Delete", TreeAction::Delete);
            break;
    }

    // MENU
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
            qDebug() << "Maximum depth reached, cannot add child nodes";
            return;
        }

        int childTypeInt = currentType + 1;
        NodeType childType = static_cast<NodeType>(childTypeInt);
        
        QIcon icon;
        QString title, label, defaultName;
        switch (childType) {
            case NodeType::VendorDevice: {
                title = "New Vendor"; 
                label = "Vendor Name:";
                defaultName = "New Vendor Category";
                icon = QIcon(":/icons/VendorDevice.png"); 
                break;
            }
            case NodeType::TestSet:{
                title = "New Test Set"; 
                label = "Test Set Name:"; 
                defaultName = "New Terminal Test Set";
                icon = QIcon(":/icons/TestSet.png");
                break;
            }   
            case NodeType::TestProject:{
                title = "New Project"; 
                label = "Project Name:"; 
                defaultName = "New Test Project"; 
                icon = QIcon(":/icons/TestProject.png");
                break;
            }  
            case NodeType::TestGroup:{
                title = "New Group"; 
                label = "Group Name:";
                defaultName = "New Test Group";
                icon = QIcon(":/icons/TestGroup.png");
                break;
            }    
            case NodeType::TestItem:{
                title = "New Test Item";
                label = "Item Name:"; 
                defaultName = "New Test Item"; 
                icon = QIcon(":/icons/TestItem.png");
                break;
            }     
            default: {
                title = "New Node"; 
                label = "Name:"; 
                defaultName = "Unnamed"; 
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
    ALL_61850_INFO allInfo;
    QString fileName = QFileDialog::getOpenFileName(this,tr("请选择scd文件"),"C:/",tr("scd文件(*.scd)"));
    QByteArray fileNameData = fileName.toLocal8Bit();
    getScd61850Info(&allInfo,fileNameData.data());
    updateDeviceTable(allInfo.ied_list,allInfo.ied_num);
}

void MainWindow::updateDeviceTable(IED_LIST *iedList, int counts)
{
    // 1. 创建并配置原始 Model
    auto *sourceModel = new BaseTableModel<IED_LIST>(this);
    sourceModel->setConfig(iedList, counts, {
                                                makeColumn<IED_LIST>("序号", &IED_LIST::id),
                                                makeColumn<IED_LIST>("名称", &IED_LIST::name),
                                                makeColumn<IED_LIST>("描述", &IED_LIST::desc),
                                                makeColumn<IED_LIST>("类型", &IED_LIST::type),
                                                makeColumn<IED_LIST>("版本号", &IED_LIST::configVersion),
                                                makeColumn<IED_LIST>("制造商", &IED_LIST::manufacturer),
                                                makeColumn<IED_LIST>("A网IP", &IED_LIST::strIPAddr1),
                                                makeColumn<IED_LIST>("B网IP", &IED_LIST::strIPAddr2),
                                            });

    auto *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sourceModel);

    proxyModel->setFilterKeyColumn(1); // 过滤第 1 列
    proxyModel->setFilterRegularExpression("^(?!.*PRS7399).*$");

    ui->deviceTableView->setModel(proxyModel);
}


void MainWindow::on_deviceTableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->deviceTableView->indexAt(pos);


    QMenu menu(this);
    // 直接在 addAction 时通过 lambda 或 槽函数处理，或者利用 exec() 的返回值
    QAction *importScdAct = menu.addAction("导入SCD");

    // 使用 exec() 阻塞获取点击的动作，这样就不需要在这里 connect 了
    QAction *selectedAct = menu.exec(ui->deviceTableView->viewport()->mapToGlobal(pos));

    if (selectedAct == importScdAct) {
        ImportScd(); // 直接调用
    }
}
