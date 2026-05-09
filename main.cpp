#include "mainwindow.h"

#include <QApplication>
#include "Comm/LogManager.h"
#include "Comm/QtLogRedirect.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogManager::instance().init("logs", spdlog::level::debug);
    QtLogRedirect::install();
    LOG_INFO("Application started");
    MainWindow w;
    w.show();
    return a.exec();
}
