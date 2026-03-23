#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Comm/TreeView.h>

#include "Utils.h"

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

private slots:
    void onTreeContextMenu(const QPoint &pos, const QString &key);
    void onTreeItemClicked(const QModelIndex &index);
    void onTableContextMenu(const QPoint &pos);
    void onImportScdRequested();
public:
    TreeView *rootTreeView;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
