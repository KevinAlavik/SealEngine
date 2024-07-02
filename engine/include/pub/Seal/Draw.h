#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include "../../backends/window.h"
#include "../../backends/files.h"
#include "../../utilities/logger.h"
#include "../../utilities/types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace SealEngine
{
    class Window;
}

namespace SealEngine
{
    class Logger;
}

namespace SealEngineDraw
{

    class Drawer
    {
    public:
        Drawer(SealEngine::Window *window, SealEngine::Logger *logger);
        ~Drawer();

        void PutPixel(int x, int y, SealEngineTypes::Color color);
        void DrawLine(int x1, int y1, int x2, int y2, SealEngineTypes::Color color);
        void DrawRect(int x, int y, int width, int height, SealEngineTypes::Color color);
        void DrawFilledRect(int x, int y, int width, int height, SealEngineTypes::Color color);
        void DrawCircle(int centerX, int centerY, int radius, SealEngineTypes::Color color);
        void DrawFilledCircle(int centerX, int centerY, int radius, SealEngineTypes::Color color);
        void DrawEllipse(int centerX, int centerY, int radiusX, int radiusY, SealEngineTypes::Color color);
        void DrawBezierCurve(int x1, int y1, int cx1, int cy1, int cx2, int cy2, int x2, int y2, SealEngineTypes::Color color);
        void DrawQuadraticCurve(int x1, int y1, int cx, int cy, int x2, int y2, SealEngineTypes::Color color);
        SealEngine::Window *GetWindow() const;

    private:
        SealEngine::Window *window;
        SealEngine::Logger *logger;

        void PlotPoints(int cx, int cy, int x, int y, SealEngineTypes::Color color);
    };

    class Texture
    {
    public:
        Texture(std::string path, SealEngine::Logger *logger = nullptr);
        ~Texture();
        void Draw(Drawer *drawer, int x, int y, int *width = nullptr, int *height = nullptr);

    private:
        std::string path;
        SealEngine::Logger *logger;
    };
}

#endif // DRAW_H
