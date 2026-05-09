#include "Comm/QtLogRedirect.h"
#include "Comm/LogManager.h"

void QtLogRedirect::install()
{
    qInstallMessageHandler(handler);
}

void QtLogRedirect::handler(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type)
    {
    case QtDebugMsg:
        LOG_DEBUG("[{}:{}] {}", context.file, context.line, localMsg.constData());
        break;
    case QtInfoMsg:
        LOG_INFO("[{}:{}] {}", context.file, context.line, localMsg.constData());
        break;
    case QtWarningMsg:
        LOG_WARN("[{}:{}] {}", context.file, context.line, localMsg.constData());
        break;
    case QtCriticalMsg:
        LOG_ERROR("[{}:{}] {}", context.file, context.line, localMsg.constData());
        break;
    case QtFatalMsg:
        LOG_CRITICAL("[{}:{}] {}", context.file, context.line, localMsg.constData());
        abort();
    }
}
