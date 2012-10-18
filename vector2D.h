#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

class Vector2D
{
    public:
        float x, y;

        Vector2D();                                // Default void constructor
        Vector2D(float x, float y);                // Default int constructor
        Vector2D(const Vector2D &obj);             // Copy constructor
        Vector2D operator=(const Vector2D& obj);
        Vector2D operator-(const Vector2D& obj);   // Operator Overload
        Vector2D operator+(const Vector2D& obj);   // Operator Overload
        Vector2D operator+=(const Vector2D& obj);   // Operator Overload

        Vector2D Rotate(float a);
};

#endif // VECTOR2D_H_INCLUDED
