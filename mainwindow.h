#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Comm/TreeView.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeComponent();
    void setupTreeData();

public:
    TreeView *rootTreeView;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
