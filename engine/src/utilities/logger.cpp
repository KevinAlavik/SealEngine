#include <utilities/logger.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace SealLogger
{
    Logger::Logger(const std::string &loggerNameSpecifier)
        : loggerName(loggerNameSpecifier) {}

    Logger::~Logger() {}

    void Logger::info(const std::string &message)
    {
        log(LogLevel::INFO, message);
    }

    void Logger::ok(const std::string &message)
    {
        log(LogLevel::OK, message);
    }

    void Logger::debug(const std::string &message)
    {
        log(LogLevel::DEBUG, message);
    }

    void Logger::warning(const std::string &message)
    {
        log(LogLevel::WARNING, message);
    }

    void Logger::error(const std::string &message)
    {
        log(LogLevel::ERROR, message);
    }

    void Logger::fatal(const std::string &message)
    {
        log(LogLevel::FATAL, message);
    }

    void Logger::log(LogLevel level, const std::string &message)
    {
        switch (level)
        {
        case LogLevel::INFO:
            printLog(message, "INFO", "\033[1;37m");
            break;
        case LogLevel::OK:
            printLog(message, "OK", "\033[1;32m");
            break;
        case LogLevel::DEBUG:
            printLog(message, "DEBUG", "\033[1;36m");
            break;
        case LogLevel::WARNING:
            printLog(message, "WARNING", "\033[1;33m");
            break;
        case LogLevel::ERROR:
            printLog(message, "ERROR", "\033[1;31m");
            break;
        case LogLevel::FATAL:
            printLog(message, "FATAL", "\033[1;35m");
            break;
        }
    }

    void Logger::printLog(const std::string &message, const std::string &prefix, const std::string &color)
    {
        std::cout << getCurrentDateTime() << " [" << prefix << "] ";

        if (!loggerName.empty())
        {
            std::cout << "[" << loggerName << "] ";
        }
        else
        {
            std::cout << "[NoName] ";
        }

        std::cout << color << message << "\033[0m" << std::endl;
    }

    std::string Logger::getCurrentDateTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm *timeInfo = std::localtime(&currentTime);

        std::stringstream ss;
        ss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
} // namespace SealLogger
