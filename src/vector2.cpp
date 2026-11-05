#include "vector2.hpp"
#include <cmath>

// Constructors
Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2(float z) : x(z), y(z) {}

// Vector arithmetic
Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 &Vector2::operator+=(const Vector2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 &Vector2::operator-=(const Vector2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 &Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
    if (scalar == 0.0f)
        return Vector2(0.0f, 0.0f); // error?
    return Vector2(x / scalar, y / scalar);
}

Vector2 &Vector2::operator/=(float scalar)
{
    if (scalar != 0.0f)
    {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

float Vector2::magnitudeSquared() const
{
    return (x * x) + (y * y);
}

float Vector2::magnitude() const
{
    return std::sqrt(magnitudeSquared());
}

Vector2 Vector2::normalized() const
{
    float mag = magnitude();
    if (mag > 0.0f)
    {
        return *this / mag;
    }
    return Vector2(0.0f, 0.0f);
}

void Vector2::normalize()
{
    float mag = magnitude();
    if (mag > 0.0f)
    {
        x /= mag;
        y /= mag;
    }
}

Vector2 operator*(float scalar, const Vector2 &vec)
{
    return vec * scalar;
}