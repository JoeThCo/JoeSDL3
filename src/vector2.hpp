#pragma once

struct Vector2
{
    float x;
    float y;

    // Constructors
    Vector2();
    Vector2(float x, float y);

    // + and -
    Vector2 operator+(const Vector2 &other) const;
    Vector2 &operator+=(const Vector2 &other);

    Vector2 operator-(const Vector2 &other) const;
    Vector2 &operator-=(const Vector2 &other);

    // * and /
    Vector2 operator*(float scalar) const;
    Vector2 &operator*=(float scalar);

    Vector2 operator/(float scalar) const;
    Vector2 &operator/=(float scalar);

    // Length / Magnitude
    float magnitudeSquared() const;
    float magnitude() const;

    // Normalization
    Vector2 normalized() const;
    void normalize();
};

// Allow scalar multiplication from the left (e.g., 5.0f * vec)
Vector2 operator*(float scalar, const Vector2 &vec);