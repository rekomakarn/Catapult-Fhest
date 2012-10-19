#include "vector2D.h"
#include "math.h"
#include <iostream>

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D &obj)
{
    x = obj.x;
    y = obj.y;
}

Vector2D Vector2D::operator=(const Vector2D& obj)
{
    x = obj.x;
    y = obj.y;
}

Vector2D Vector2D::operator-(const Vector2D& obj)
{
    int newX = x - obj.x;
    int newY = y - obj.y;
    return Vector2D(newX, newY);
}

Vector2D Vector2D::operator+(const Vector2D& obj)
{
    int newX = x + obj.x;
    int newY = y + obj.y;
    return Vector2D(newX, newY);
}

Vector2D Vector2D::operator+=(const Vector2D& obj)
{
    int newX = x + obj.x;
    int newY = y + obj.y;
    return Vector2D(newX, newY);
}


Vector2D Vector2D::Rotate(float a)
{
    a = a * M_PI / 180;
	float x2 = x * cosf(a) - y * sinf(a);
	float y2 = x * sinf(a) + y * cosf(a);
	return Vector2D(x2,y2);
}
