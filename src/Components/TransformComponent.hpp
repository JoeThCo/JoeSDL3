#pragma once
#include "Component.hpp"
#include "../Vector2.hpp"

class TransformComponent : public Component
{
public:
    float x, y;
    float w, h;

    TransformComponent(float startX, float startY, float width, float height)
        : x(startX), y(startY), w(width), h(height) {}

    TransformComponent(Vector2 pos, Vector2 size)
        : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
};