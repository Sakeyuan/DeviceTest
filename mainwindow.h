#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Comm/TreeView.h>

#include "Utils.h"
#include "ScdParse/interface.h"
#include "Comm/BaseTableModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using namespace DeviceTest;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeComponent();
    void setupTreeData();
    QAction* addMenuAction(QMenu *parent, const QString &text, TreeAction actionType, const QIcon &icon = QIcon()); 
    void handleTreeAction(TreeAction type, const QString &key);
    void ImportScd();
    void updateDeviceTable(IED_LIST* iedList,int counts);

private slots:
    void onTreeContextMenu(const QPoint &pos, const QString &key);
    void onTreeItemClicked(const QModelIndex &index);
    void on_deviceTableView_customContextMenuRequested(const QPoint &pos);

public:
    TreeView *rootTreeView;

private:
    Ui::MainWindow *ui;
    QStandardItemModel *deviceTableViewModel;
};
#endif // MAINWINDOW_H
