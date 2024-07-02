#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../utilities/logger.h"
#include "../utilities/types.h"

namespace SealWindow
{

    class SealWindowHookHandleEvent
    {
    public:
        virtual void handleEventsHook(SDL_Event &event) = 0;
        virtual ~SealWindowHookHandleEvent() {}
    };

    class Window
    {
    public:
        Window(const std::string &windowTitle, int windowWidth, int windowHeight);
        ~Window();
        bool spawn();
        void clear(SealEngineTypes::Color color);
        void present();
        bool isRunning() const;
        void handleEvents();
        SDL_Window *getWindow() const;
        SDL_Renderer *getRenderer() const;
        SDL_Texture *getRendererTexture() const;
        void attachHandleEventHook(SealWindowHookHandleEvent *hook);
        int getWidth() const;
        int getHeight() const;
        void kill();
        bool verbose;

    private:
        std::string title;
        int width;
        int height;
        bool running;

        SDL_Window *window;
        SDL_Texture *renderTexture;
        SDL_Renderer *renderer;
        SealLogger::Logger logger;
        SealWindowHookHandleEvent *handleEventHook;
    };

} // namespace SealWindow

#endif // WINDOW_H
