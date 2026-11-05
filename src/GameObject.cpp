#include "GameObject.hpp"

// --- GameObject Implementation ---
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
        if (keystate[SDL_SCANCODE_W])
            rect.y -= speed * deltaTime;
        if (keystate[SDL_SCANCODE_S])
            rect.y += speed * deltaTime;
        if (keystate[SDL_SCANCODE_A])
            rect.x -= speed * deltaTime;
        if (keystate[SDL_SCANCODE_D])
            rect.x += speed * deltaTime;
    }
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}