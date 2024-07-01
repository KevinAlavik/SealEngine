#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <utilities/logger.h>

namespace SealWindow
{

    class SealWindowHookHandleEvent
    {
    public:
        virtual void handleEventsHook(SDL_Event &event) = 0;
        virtual ~SealWindowHookHandleEvent() {}
    };

    class SealWindowHookPresent
    {
    public:
        virtual void presentHook() = 0;
        virtual ~SealWindowHookPresent() {}
    };

    class Window
    {
    public:
        Window(const std::string &windowTitle, int windowWidth, int windowHeight);
        ~Window();
        bool spawn();
        void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void present();
        bool isRunning() const;
        void handleEvents();
        SDL_Window *getWindow() const;
        SDL_Renderer *getRenderer() const;
        void attachHandleEventHook(SealWindowHookHandleEvent *hook);
        void attachPresentHook(SealWindowHookPresent *hook);

    private:
        std::string title;
        int width;
        int height;
        bool running;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SealLogger::Logger logger;
        SealWindowHookHandleEvent *handleEventHook;
        SealWindowHookPresent *presentHook;
    };

} // namespace SealWindow

#endif // WINDOW_H
