#pragma once
#include "Component.hpp"
#include "../Vector2.hpp"

class TransformComponent : public Component
{
public:
    float x, y;
    float w, h;
    float rotation;

    TransformComponent(float startX, float startY, float width, float height, float rot = 0.0f)
        : x(startX), y(startY), w(width), h(height), rotation(rot) {}

    TransformComponent(Vector2 pos, Vector2 size, float rot = 0.0f)
        : x(pos.x), y(pos.y), w(size.x), h(size.y), rotation(rot) {}

    Vector2 getPosition()
    {
        return Vector2(x, y);
    }

    Vector2 getCenter() const
    {
        float centerX = x - (w * 0.5f);
        float centerY = y - (h * 0.5f);
        return Vector2(centerX, centerY);
    }

    void center()
    {
        move(getCenter());
    }

    void translate(const Vector2 &offset)
    {
        x += offset.x;
        y += offset.y;
    }

    void move(const Vector2 &newPos)
    {
        x = newPos.x;
        y = newPos.y;
    }
};