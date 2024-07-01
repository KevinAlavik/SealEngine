#ifndef SEAL_H
#define SEAL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <functional>
#include <chrono>
#include <thread>

#include "../../backends/window.h"
#include "../../utilities/logger.h"

namespace SealEngine
{
    class Window
    {
    public:
        Window(const std::string &windowTitle, int windowWidth, int windowHeight);
        ~Window();
        void Spawn(std::function<void()> setupFunction, std::function<void()> updateFunction);

    private:
        SealWindow::Window window;
        SealLogger::Logger logger;
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
        void Log(LogLevel level, const std::string &message);

    private:
        SealLogger::Logger logger;
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
