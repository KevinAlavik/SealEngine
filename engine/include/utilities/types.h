#ifndef TYPES_H
#define TYPES_H

namespace SealEngineTypes
{
    class Color
    {
    public:
        Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255)
            : r(r), g(g), b(b), a(a) {}

        unsigned char Red() const { return r; }
        unsigned char Green() const { return g; }
        unsigned char Blue() const { return b; }
        unsigned char Alpha() const { return a; }

    private:
        unsigned char r, g, b, a;
    };
}

#endif // TYPES_H