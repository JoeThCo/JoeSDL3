#pragma once
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"

enum class ShapeType
{
    FilledRect,
    OutlinedRect,
    Circle
};

class ShapeRendererComponent : public Component
{
private:
    ShapeType shapeType;
    SDL_Color color;

public:
    ShapeRendererComponent(ShapeType type, SDL_Color _color)
        : shapeType(type), color(_color) {}

    void render(SDL_Renderer *renderer) override
    {
        if (auto *transform = Owner->getComponent<TransformComponent>())
        {
            SDL_FRect rect = {transform->x, transform->y, transform->w, transform->h};

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            switch (shapeType)
            {
            case ShapeType::FilledRect:
            {
                SDL_RenderFillRect(renderer, &rect);
                break;
            }
            case ShapeType::OutlinedRect:
            {
                SDL_RenderRect(renderer, &rect);
                break;
            }
            case ShapeType::Circle:
            {
                float centerX = transform->x + transform->w * 0.5f;
                float centerY = transform->y + transform->h * 0.5f;
                float radius = (transform->w < transform->h ? transform->w : transform->h) * 0.5f;

                int xmin = static_cast<int>(transform->x);
                int xmax = static_cast<int>(transform->x + transform->w);
                int ymin = static_cast<int>(transform->y);
                int ymax = static_cast<int>(transform->y + transform->h);

                for (int y = ymin; y <= ymax; ++y)
                {
                    for (int x = xmin; x <= xmax; ++x)
                    {
                        float dx = x - centerX;
                        float dy = y - centerY;
                        if (dx * dx + dy * dy <= radius * radius)
                        {
                            SDL_RenderPoint(renderer, static_cast<float>(x), static_cast<float>(y));
                        }
                    }
                }
                break;
            }
            }
        }
    }
};