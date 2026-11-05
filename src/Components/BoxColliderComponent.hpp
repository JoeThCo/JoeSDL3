#pragma once
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"

class BoxColliderComponent : public Component
{
public:
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    BoxColliderComponent(float w = 0.0f, float h = 0.0f, float ox = 0.0f, float oy = 0.0f)
        : width(w), height(h), offsetX(ox), offsetY(oy) {}

    SDL_FRect getRect() const
    {
        if (auto *transform = Owner->getComponent<TransformComponent>())
        {
            float w = (width > 0.0f) ? width : transform->w;
            float h = (height > 0.0f) ? height : transform->h;
            return {transform->x + offsetX, transform->y + offsetY, w, h};
        }
        return {0, 0, 0, 0};
    }
};