#pragma once
#include "Component.hpp"

class TransformComponent : public Component
{
public:
    float x, y;
    float w, h;

    TransformComponent(float startX, float startY, float width, float height)
        : x(startX), y(startY), w(width), h(height) {}
};