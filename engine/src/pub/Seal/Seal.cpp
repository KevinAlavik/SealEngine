#include <pub/Seal/Seal.h>

namespace SealEngine
{
    // Window
    Window::Window(const std::string &title, int windowWidth, int windowHeight)
        : window(new SealWindow::Window(title, windowWidth, windowHeight)), logger(new SealLogger::Logger("SealWindow"))
    {
    }

    Window::~Window()
    {
        if (window != nullptr)
        {
            delete window;
            window = nullptr;
        }
        if (logger != nullptr)
        {
            delete logger;
            logger = nullptr;
        }
    }

    void Window::Spawn(std::function<void()> setupFunction, std::function<void()> updateFunction)
    {
        if (!window->spawn())
        {
            logger->fatal("Failed to spawn window.");
            return;
        }

        setupFunction();

        using namespace std::chrono;
        auto lastTime = high_resolution_clock::now();

        while (window->isRunning())
        {
            window->handleEvents();
            updateFunction();
            window->present();

            auto currentTime = high_resolution_clock::now();
            duration<float> elapsedTime = currentTime - lastTime;
            lastTime = currentTime;

            float fps = 1.0f / elapsedTime.count();

            std::ostringstream fpsStream;
            fpsStream << std::fixed << std::setprecision(2) << "FPS: " << fps;
            std::string fpsString = fpsStream.str();

            if (window->verbose)
                logger->debug(fpsString);
        }
    }

    void Window::Clear(SealEngineTypes::Color color)
    {
        window->clear(color);
    }

    void Window::Quit()
    {
        delete window;
        window = nullptr;
    }

    SealWindow::Window *Window::GetWindow()
    {
        return window;
    }

    int Window::GetWindowWidth() const
    {
        return window->getWidth();
    }

    int Window::GetWindowHeight() const
    {
        return window->getHeight();
    }

    // Logger
    Logger::Logger(const std::string &name) : logger(new SealLogger::Logger(name))
    {
    }

    Logger::~Logger()
    {
    }

    void Logger::Log(LogLevel level, const std::string &message)
    {
        switch (level)
        {
        case SealEngine::Logger::LogLevel::OK:
            logger->ok(message);
            break;
        case SealEngine::Logger::LogLevel::DEBUG:
            logger->debug(message);
            break;
        case SealEngine::Logger::LogLevel::INFO:
            logger->info(message);
            break;
        case SealEngine::Logger::LogLevel::ERROR:
            logger->error(message);
            break;
        case SealEngine::Logger::LogLevel::FATAL:
            logger->fatal(message);
            break;
        default:
            logger->error("Unknown log level.");
            break;
        }
    }

    SealLogger::Logger *Logger::GetLogger()
    {
        return logger;
    }

    // Timer
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