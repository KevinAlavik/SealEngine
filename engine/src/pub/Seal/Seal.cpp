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
        window->kill();
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

    void Window::AttatchEventHook(SealWindow::SealWindowHookHandleEvent *hook)
    {
        window->attachHandleEventHook(hook);
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
        case SealEngine::Logger::LogLevel::WARNING:
            logger->warning(message);
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

    // Sprite Manager
    Sprite::Sprite(const std::string texture, SealEngineTypes::Vector2 pos, SealEngineTypes::Vector2 size, SealEngineContentManager::SealEngineContentManager *contentManager, SealEngineDraw::Drawer *drawer, SealEngine::Logger *logger)
    {
        this->texture = contentManager->GetAsset<SealEngineDraw::Texture>(texture);
        this->position = pos;
        this->size = size;
        this->visible = false;
        this->contentManager = contentManager;
        this->drawer = drawer;
        this->logger = logger;
    }

    Sprite::~Sprite()
    {
        this->texture = nullptr;
        this->position = SealEngineTypes::Vector2(0, 0);
        this->size = SealEngineTypes::Vector2(0, 0);
        this->contentManager = nullptr;
        this->drawer = nullptr;
        this->logger = nullptr;
        this->visible = false;
    }

    void Sprite::Hide()
    {
        this->visible = false;
    }

    void Sprite::Show()
    {
        this->visible = true;
    }

    void Sprite::SetTexture(const std::string &texture)
    {
        this->texture = contentManager->GetAsset<SealEngineDraw::Texture>(texture);
    }

    void Sprite::Move(SealEngineTypes::Vector2 pos)
    {
        this->position = pos;
    }

    void Sprite::Resize(SealEngineTypes::Vector2 size)
    {
        this->size = size;
    }

    void Sprite::Update()
    {
        if (visible)
        {
            texture->Draw(drawer, position.X, position.Y, &size.X, &size.Y);
        }
    }

    SealEngineTypes::Vector2 Sprite::GetPosition() const
    {
        return position;
    }
}