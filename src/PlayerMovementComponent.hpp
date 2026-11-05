#pragma once
#include <SDL3/SDL.h>
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"

class PlayerMovementComponent : public Component
{
private:
    float speed;

public:
    PlayerMovementComponent(float movementSpeed) : speed(movementSpeed) {}

    void update(float deltaTime) override
    {
        // 1. Get current keyboard state from SDL3
        const bool *keystate = SDL_GetKeyboardState(nullptr);
        if (!keystate)
            return;

        // 2. Build directional input using your custom Vector2 class
        Vector2 inputDir(0.0f, 0.0f);

        if (keystate[SDL_SCANCODE_W])
            inputDir.y -= 1.0f; // Move Up
        if (keystate[SDL_SCANCODE_S])
            inputDir.y += 1.0f; // Move Down
        if (keystate[SDL_SCANCODE_A])
            inputDir.x -= 1.0f; // Move Left
        if (keystate[SDL_SCANCODE_D])
            inputDir.x += 1.0f; // Move Right

        // 3. Normalize the vector so diagonal movement isn't faster (magnitude = 1)
        inputDir.normalize();

        // 4. Apply movement to the TransformComponent on this same GameObject
        if (auto *transform = Owner->getComponent<TransformComponent>())
        {
            transform->x += inputDir.x * speed * deltaTime;
            transform->y += inputDir.y * speed * deltaTime;
        }
    }
};