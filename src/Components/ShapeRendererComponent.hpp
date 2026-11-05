#pragma once
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"

class ShapeRendererComponent : public Component
{
private:
    Uint8 r, g, b, a;

public:
    ShapeRendererComponent(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    void render(SDL_Renderer *renderer) override
    {
        if (auto *transform = Owner->getComponent<TransformComponent>())
        {
            SDL_FRect rect = {transform->x, transform->y, transform->w, transform->h};

            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};