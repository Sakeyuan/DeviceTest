#include "Comm/LogManager.h"
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <QDir>

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
    spdlog::shutdown();
}

LogManager& LogManager::instance()
{
    static LogManager instance;
    return instance;
}

void LogManager::init(const QString& logDir, spdlog::level::level_enum level)
{
    QDir dir;
    if (!dir.exists(logDir))
        dir.mkpath(logDir);

    std::string logPath = (logDir + "/app.log").toStdString();

    // 控制台 sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // 按大小滚动（5MB，3个文件）
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        logPath, 1024 * 1024 * 5, 3);

    // 按天日志
    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
        (logDir + "/daily.log").toStdString(), 0, 0);

    std::vector<spdlog::sink_ptr> sinks { console_sink, rotating_sink, daily_sink };

    m_logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

    m_logger->set_level(level);
    m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [thread %t] %v");

    spdlog::register_logger(m_logger);

    // 自动 flush
    spdlog::flush_every(std::chrono::seconds(3));
}

std::shared_ptr<spdlog::logger> LogManager::getLogger()
{
    return m_logger;
}

std::shared_ptr<spdlog::logger> LogManager::getModuleLogger(const std::string& name)
{
    auto logger = spdlog::get(name);
    if (!logger)
    {
        logger = m_logger->clone(name);
        spdlog::register_logger(logger);
    }
    return logger;
}

void LogManager::flush()
{
    if (m_logger)
        m_logger->flush();
}
