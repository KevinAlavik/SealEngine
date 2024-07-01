#include <pub/Seal/Draw.h>
#include <SDL2/SDL.h>

namespace SealEngineDraw
{
    Drawer::Drawer(SealEngine::Window *window, SealEngine::Logger *logger) : window(window), logger(logger)
    {
    }

    Drawer::~Drawer() = default;

    void Drawer::PutPixel(int x, int y, const SealEngineDraw::Color color)
    {
        SDL_Renderer *renderer = window->GetWindow()->getRenderer();
        SDL_SetRenderDrawColor(renderer, color.Red(), color.Green(), color.Blue(), color.Alpha());
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
