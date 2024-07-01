#ifndef DRAW_H
#define DRAW_H

#include "../../backends/window.h"
#include "../../utilities/logger.h"
#include "Seal.h"

namespace SealEngineDraw
{

    class Color
    {
    public:
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
            : r(r), g(g), b(b), a(a) {}

        unsigned char Red() const { return r; }
        unsigned char Green() const { return g; }
        unsigned char Blue() const { return b; }
        unsigned char Alpha() const { return a; }

    private:
        unsigned char r, g, b, a;
    };

    class Drawer
    {
    public:
        Drawer(SealEngine::Window *window, SealEngine::Logger *logger);
        ~Drawer();
        void PutPixel(int x, int y, SealEngineDraw::Color color);

    private:
        SealEngine::Window *window;
        SealEngine::Logger *logger;
    };
}

#endif // DRAW_H
