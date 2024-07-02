#ifndef SEAL_H
#define SEAL_H

#include <functional>
#include <chrono>
#include <thread>

#include "../../backends/window.h"
#include "../../backends/content.h"
#include "../../utilities/logger.h"
#include "../../utilities/types.h"

namespace SealEngine
{
    class Window
    {
    public:
        Window(const std::string &windowTitle, int windowWidth, int windowHeight);
        ~Window();
        void Spawn(std::function<void()> setupFunction, std::function<void()> updateFunction);
        void Clear(SealEngineTypes::Color color);
        void Quit();
        SealWindow::Window *GetWindow();
        int GetWindowWidth() const;
        int GetWindowHeight() const;

    private:
        SealWindow::Window *window;
        SealLogger::Logger *logger;
    };

    class Logger
    {
    public:
        enum class LogLevel
        {
            INFO,
            OK,
            DEBUG,
            ERROR,
            FATAL
        };

        Logger(const std::string &name);
        ~Logger();
        void Log(LogLevel level, const std::string &message);
        SealLogger::Logger *GetLogger();

    private:
        SealLogger::Logger *logger;
    };

    class Timer
    {
    public:
        static void SleepMilliseconds(int milliseconds);
        static void SleepSeconds(int seconds);
        static long long GetCurrentTimeMilliseconds();
        static long long GetCurrentTimeSeconds();
    };
}

#endif // SEAL_H
