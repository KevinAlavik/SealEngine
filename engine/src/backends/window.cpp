#include <backends/window.h>

namespace SealWindow
{

    Window::Window(const std::string &windowTitle, int windowWidth, int windowHeight)
        : verbose(false), title(windowTitle), width(windowWidth), height(windowHeight), running(false), window(nullptr), renderTexture(nullptr), renderer(nullptr), logger("SealWindow")
    {
        logger.info("Window created");
    }

    Window::~Window()
    {
        if (renderTexture)
        {
            SDL_DestroyTexture(renderTexture);
            renderTexture = nullptr;
        }
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
    }

    bool Window::spawn()
    {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window)
        {
            logger.error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        if (!renderer)
        {
            logger.error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }

        renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        if (!renderTexture)
        {
            logger.error("Failed to create render texture! SDL_Error: " + std::string(SDL_GetError()));
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }

        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP))
        {
            logger.error("Failed to initialize SDL_Image! SDL_Error: " + std::string(SDL_GetError()));
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }

        running = true;
        return true;
    }

    void Window::clear(SealEngineTypes::Color color)
    {
        SDL_SetRenderTarget(renderer, renderTexture);

        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Window::present()
    {
        SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
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

            std::lock_guard<std::mutex> lock(hooksMutex);
            for (auto &hook : eventHooks)
            {
                hook->handleEventsHook(event);
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

    SDL_Texture *Window::getRendererTexture() const
    {
        return renderTexture;
    }

    void Window::attachHandleEventHook(SealWindowHookHandleEvent *hook)
    {
        std::lock_guard<std::mutex> lock(hooksMutex);
        eventHooks.push_back(hook);
        logger.info("Event hook attached");
    }

    int Window::getWidth() const
    {
        return width;
    }

    int Window::getHeight() const
    {
        return height;
    }

} // namespace SealWindow
