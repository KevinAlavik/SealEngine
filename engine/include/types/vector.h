#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

namespace SealEngineTypes
{
    class Vector2
    {
    public:
        int X, Y;

        Vector2() : X(0), Y(0) {}
        Vector2(int x, int y) : X(x), Y(y) {}

        int GetX() const { return X; }
        int GetY() const { return Y; }

        void SetX(int newX) { X = newX; }
        void SetY(int newY) { Y = newY; }

        Vector2 Add(const Vector2 &v) const
        {
            return Vector2(X + v.X, Y + v.Y);
        }

        Vector2 Subtract(const Vector2 &v) const
        {
            return Vector2(X - v.X, Y - v.Y);
        }

        Vector2 Multiply(int scalar) const
        {
            return Vector2(X * scalar, Y * scalar);
        }

        Vector2 Divide(int scalar) const
        {
            if (scalar != 0)
            {
                return Vector2(X / scalar, Y / scalar);
            }
            else
            {
                std::cerr << "Error: Division by zero!\n";
                return *this;
            }
        }

        float Length() const
        {
            return std::sqrt(X * X + Y * Y);
        }

        void Normalize()
        {
            float len = Length();
            if (len != 0)
            {
                X /= len;
                Y /= len;
            }
        }

        static int Dot(const Vector2 &v1, const Vector2 &v2)
        {
            return v1.X * v2.X + v1.Y * v2.Y;
        }

        static float Distance(const Vector2 &v1, const Vector2 &v2)
        {
            float dx = v1.X - v2.X;
            float dy = v1.Y - v2.Y;
            return std::sqrt(dx * dx + dy * dy);
        }

        Vector2 operator+(const Vector2 &v) const
        {
            return Add(v);
        }

        Vector2 operator-(const Vector2 &v) const
        {
            return Subtract(v);
        }

        Vector2 operator*(int scalar) const
        {
            return Multiply(scalar);
        }

        Vector2 operator/(int scalar) const
        {
            return Divide(scalar);
        }

        bool operator==(const Vector2 &v) const
        {
            return X == v.X && Y == v.Y;
        }

        bool operator!=(const Vector2 &v) const
        {
            return !(*this == v);
        }
    };
}

#endif // VECTOR_H