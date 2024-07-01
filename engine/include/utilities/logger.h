#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

namespace SealLogger
{

    enum class LogLevel
    {
        INFO,
        OK,
        DEBUG,
        ERROR,
        FATAL
    };

    class Logger
    {
    public:
        Logger(const std::string &loggerNameSpecifier);
        ~Logger();

        void info(const std::string &message);
        void ok(const std::string &message);
        void debug(const std::string &message);
        void error(const std::string &message);
        void fatal(const std::string &message);

    private:
        std::string loggerName;

        void log(LogLevel level, const std::string &message);
        void printLog(const std::string &message, const std::string &prefix, const std::string &color);
        std::string getCurrentDateTime();
    };

} // namespace SealLogger

#endif // LOGGER_H
