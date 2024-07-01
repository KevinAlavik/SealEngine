#include <pub/Seal/Seal.h>

namespace SealEngine
{
    Window::Window(const std::string &title, int windowWidth, int windowHeight) : window(SealWindow::Window(title, windowWidth, windowHeight)), logger(SealLogger::Logger("SealWindow"))
    {
        window.clear(0, 0, 0, 255);
    }

    Window::~Window()
    {
        window.~Window();
    }

    void Window::Spawn(std::function<void()> setupFunction, std::function<void()> updateFunction)
    {
        if (!window.spawn())
        {
            logger.fatal("Failed to spawn window.");
            return;
        }

        setupFunction();

        while (window.isRunning())
        {
            window.handleEvents();
            updateFunction();
            window.present();
        }
    }

    Logger::Logger(const std::string &name) : logger(SealLogger::Logger(name))
    {
    }

    void Logger::Log(LogLevel level, const std::string &message)
    {
        switch (level)
        {
        case SealEngine::Logger::LogLevel::OK:
            logger.ok(message);
            break;
        case SealEngine::Logger::LogLevel::DEBUG:
            logger.debug(message);
            break;
        case SealEngine::Logger::LogLevel::INFO:
            logger.info(message);
            break;
        case SealEngine::Logger::LogLevel::ERROR:
            logger.error(message);
            break;
        case SealEngine::Logger::LogLevel::FATAL:
            logger.fatal(message);
            break;
        default:
            logger.error("Unknown log level.");
            break;
        }

        return;
    }

    void Timer::SleepMilliseconds(int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void Timer::SleepSeconds(int seconds)
    {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    long long Timer::GetCurrentTimeMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    long long Timer::GetCurrentTimeSeconds()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }
}