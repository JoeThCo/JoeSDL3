#pragma once
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "../Vector2.hpp"

class PlayerMovementComponent : public Component
{
private:
    float speed;

public:
    PlayerMovementComponent(float movementSpeed) : speed(movementSpeed) {}

    void update(float deltaTime) override
    {
        const bool *keystate = SDL_GetKeyboardState(nullptr);
        if (!keystate)
            return;

        Vector2 inputDir(0.0f, 0.0f);

        if (keystate[SDL_SCANCODE_W])
            inputDir.y -= 1.0f;
        if (keystate[SDL_SCANCODE_S])
            inputDir.y += 1.0f;
        if (keystate[SDL_SCANCODE_A])
            inputDir.x -= 1.0f;
        if (keystate[SDL_SCANCODE_D])
            inputDir.x += 1.0f;

        inputDir.normalize();

        if (auto *transform = Owner->getComponent<TransformComponent>())
        {
            transform->x += inputDir.x * speed * deltaTime;
            transform->y += inputDir.y * speed * deltaTime;
        }
    }
};