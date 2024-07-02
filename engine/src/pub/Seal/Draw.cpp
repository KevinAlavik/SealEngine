#include <pub/Seal/Draw.h>

namespace SealEngineDraw
{
    // Drawer
    Drawer::Drawer(SealEngine::Window *window, SealEngine::Logger *logger)
        : window(window), logger(logger)
    {
    }

    Drawer::~Drawer()
    {
        if (logger != nullptr)
        {
            delete logger;
            logger = nullptr;
        }
    };

    void Drawer::PutPixel(int x, int y, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawLine(int x1, int y1, int x2, int y2, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawRect(int x, int y, int width, int height, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawFilledRect(int x, int y, int width, int height, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawCircle(int centerX, int centerY, int radius, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());

        int x = radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (radius << 1);

        while (x >= y)
        {
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);

            if (err <= 0)
            {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0)
            {
                x--;
                dx += 2;
                err += dx - (radius << 1);
            }
        }

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawFilledCircle(int centerX, int centerY, int radius, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());

        int x = radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (radius << 1);

        while (x >= y)
        {
            SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
            SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
            SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
            SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

            if (err <= 0)
            {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0)
            {
                x--;
                dx += 2;
                err += dx - (radius << 1);
            }
        }

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawEllipse(int centerX, int centerY, int radiusX, int radiusY, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());

        double theta = 0.0;
        int x, y;
        while (theta < 2 * M_PI)
        {
            x = static_cast<int>(centerX + radiusX * cos(theta));
            y = static_cast<int>(centerY + radiusY * sin(theta));
            SDL_RenderDrawPoint(renderer, x, y);
            theta += 0.01;
        }

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawBezierCurve(int x1, int y1, int cx1, int cy1, int cx2, int cy2, int x2, int y2, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());

        const int STEPS = 100;
        float t = 0.0f;
        for (int i = 0; i <= STEPS; ++i)
        {
            float tNext = static_cast<float>(i) / STEPS;
            int px = static_cast<int>((1 - t) * (1 - t) * (1 - t) * x1 +
                                      3 * (1 - t) * (1 - t) * t * cx1 +
                                      3 * (1 - t) * t * t * cx2 +
                                      t * t * t * x2);
            int py = static_cast<int>((1 - t) * (1 - t) * (1 - t) * y1 +
                                      3 * (1 - t) * (1 - t) * t * cy1 +
                                      3 * (1 - t) * t * t * cy2 +
                                      t * t * t * y2);
            SDL_RenderDrawPoint(renderer, px, py);
            t = tNext;
        }

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::DrawQuadraticCurve(int x1, int y1, int cx, int cy, int x2, int y2, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());

        const int STEPS = 100;
        float t = 0.0f;
        for (int i = 0; i <= STEPS; ++i)
        {
            float tNext = static_cast<float>(i) / STEPS;
            int px = static_cast<int>((1 - t) * (1 - t) * x1 +
                                      2 * (1 - t) * t * cx +
                                      t * t * x2);
            int py = static_cast<int>((1 - t) * (1 - t) * y1 +
                                      2 * (1 - t) * t * cy +
                                      t * t * y2);
            SDL_RenderDrawPoint(renderer, px, py);
            t = tNext;
        }

        SDL_SetRenderTarget(renderer, nullptr);
    }

    void Drawer::PlotPoints(int cx, int cy, int x, int y, SealEngineTypes::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = window->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        SDL_SetRenderTarget(renderer, nullptr);
    }

    SealEngine::Window *Drawer::GetWindow() const
    {
        return window;
    }

    // Texture
    Texture::Texture(std::string path, SealEngine::Logger *logger) : path(path), logger(logger)
    {
        if (logger == nullptr)
        {
            logger = new SealEngine::Logger(path);
        }
    }

    Texture::~Texture()
    {
    }

    void Texture::Draw(Drawer *drawer, int x, int y, int *width, int *height)
    {
        SDL_Renderer *renderer = drawer->GetWindow()->GetWindow()->getRenderer();
        SDL_Texture *renderTexture = drawer->GetWindow()->GetWindow()->getRendererTexture();
        SDL_SetRenderTarget(renderer, renderTexture);

        SDL_Surface *surface = IMG_Load(path.c_str());
        if (!surface)
        {
            logger->Log(SealEngine::Logger::LogLevel::ERROR, "Failed to load image: " + path);
            logger->Log(SealEngine::Logger::LogLevel::ERROR, IMG_GetError());
            return;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            logger->Log(SealEngine::Logger::LogLevel::ERROR, "Failed to create texture from surface: " + path);
            SDL_FreeSurface(surface);
            return;
        }

        SDL_Rect destination;
        destination.x = x;
        destination.y = y;
        destination.w = (width != nullptr) ? *width : surface->w;
        destination.h = (height != nullptr) ? *height : surface->h;

        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer, texture, NULL, &destination);
        SDL_DestroyTexture(texture);
        SDL_SetRenderTarget(renderer, nullptr);
    }
}
