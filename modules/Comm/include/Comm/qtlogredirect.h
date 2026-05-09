#ifndef QTLOGREDIRECT_H
#define QTLOGREDIRECT_H

#include <QtGlobal>

class QtLogRedirect
{
public:
    static void install();
    static void handler(QtMsgType type,const QMessageLogContext &context,const QString &msg);
};

#endif
