#include "GameObject.hpp"

// --- GameObject ---
GameObject::GameObject(float x, float y, float w, float h) : rect{x, y, w, h} {}

SDL_FRect GameObject::getRect() const
{
    return rect;
}

// --- Player ---
Player::Player(float x, float y, float w, float h, float speed)
    : GameObject(x, y, w, h), speed(speed) {}

void Player::update(float deltaTime, const bool *keystate = nullptr)
{
    // Add movement/update logic here
    if (keystate)
    {
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

        rect.x += inputDir.x * speed * deltaTime;
        rect.y += inputDir.y * speed * deltaTime;
    }
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}