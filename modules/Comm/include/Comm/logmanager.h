#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <memory>
#include <QString>
#include <spdlog/spdlog.h>

class LogManager
{
public:
    static LogManager& instance();

    void init(const QString& logDir,spdlog::level::level_enum level = spdlog::level::debug);

    std::shared_ptr<spdlog::logger> getLogger();
    std::shared_ptr<spdlog::logger> getModuleLogger(const std::string& name);

    void flush();

private:
    LogManager();
    ~LogManager();

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

#define LOG_TRACE(...)  LogManager::instance().getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)  LogManager::instance().getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)   LogManager::instance().getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)   LogManager::instance().getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  LogManager::instance().getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) LogManager::instance().getLogger()->critical(__VA_ARGS__)

#endif
