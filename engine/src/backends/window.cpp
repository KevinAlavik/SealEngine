#include <backends/window.h>

namespace SealWindow
{

    Window::Window(const std::string &windowTitle, int windowWidth, int windowHeight)
        : title(windowTitle), width(windowWidth), height(windowHeight), running(false), window(nullptr), renderer(nullptr), logger("SealWindow"), handleEventHook(nullptr), presentHook(nullptr)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            logger.error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
        }
    }

    Window::~Window()
    {
        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }

    bool Window::spawn()
    {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window)
        {
            logger.error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            logger.error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }

        running = true;
        return true;
    }

    void Window::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void Window::present()
    {
        SDL_RenderPresent(renderer);

        if (presentHook)
        {
            presentHook->presentHook();
        }
    }

    bool Window::isRunning() const
    {
        return running;
    }

    void Window::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (handleEventHook)
            {
                handleEventHook->handleEventsHook(event);
            }
        }
    }

    SDL_Window *Window::getWindow() const
    {
        return window;
    }

    SDL_Renderer *Window::getRenderer() const
    {
        return renderer;
    }

    void Window::attachHandleEventHook(SealWindowHookHandleEvent *hook)
    {
        handleEventHook = hook;
    }

    void Window::attachPresentHook(SealWindowHookPresent *hook)
    {
        presentHook = hook;
    }

} // namespace SealWindow
