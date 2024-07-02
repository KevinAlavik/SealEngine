#ifndef SEAL_H
#define SEAL_H

#include <functional>
#include <chrono>
#include <thread>

#include <SDL2/SDL.h>

#include "../../backends/window.h"
#include "../../backends/content.h"
#include "../../utilities/logger.h"
#include "../../utilities/types.h"
#include "../../types/vector.h"

#include "Draw.h"

namespace SealEngine
{
    // Keyboard Manager
    class Keyboard
    {
    public:
        using KeyHandler = std::function<void()>;

        static void RegisterEvent(const std::string &key, KeyHandler handler)
        {
            instance().keyHandlers[SDL_GetScancodeFromKey(SDL_GetKeyFromName(key.c_str()))] = handler;
        }

        static void HandleEvent(const SDL_Event &event)
        {
            if (event.type == SDL_KEYDOWN)
            {
                auto it = instance().keyHandlers.find(event.key.keysym.scancode);
                if (it != instance().keyHandlers.end())
                {
                    it->second();
                }
            }
        }

    private:
        std::unordered_map<SDL_Scancode, KeyHandler> keyHandlers;

        static Keyboard &instance()
        {
            static Keyboard instance;
            return instance;
        }
    };

    class KeyboardEvent : public SealWindow::SealWindowHookHandleEvent
    {
    public:
        void handleEventsHook(SDL_Event &event) override
        {
            Keyboard::HandleEvent(event);
        }
    };

    // Window Manager
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
        void AttatchEventHook(SealWindow::SealWindowHookHandleEvent *hook);

    private:
        SealWindow::Window *window;
        SealLogger::Logger *logger;
    };

    // Logger manager
    class Logger
    {
    public:
        enum class LogLevel
        {
            INFO,
            OK,
            DEBUG,
            ERROR,
            WARNING,
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

    // Sprite Manager
    class Sprite
    {
    public:
        Sprite(const std::string texture, SealEngineTypes::Vector2 pos, SealEngineTypes::Vector2 size, SealEngineContentManager::SealEngineContentManager *contentManager, SealEngineDraw::Drawer *drawer, SealEngine::Logger *logger);
        ~Sprite();
        void Hide();
        void Show();
        void Move(SealEngineTypes::Vector2 pos);
        void Resize(SealEngineTypes::Vector2 size);
        void SetTexture(const std::string &texture);
        SealEngineTypes::Vector2 GetPosition() const;
        void Update();

    private:
        SealEngineDraw::Texture *texture;
        SealEngineTypes::Vector2 position;
        SealEngineTypes::Vector2 size;
        SealEngineContentManager::SealEngineContentManager *contentManager;
        SealEngineDraw::Drawer *drawer;
        SealEngine::Logger *logger;
        bool visible;
    };
}

#endif // SEAL_H
