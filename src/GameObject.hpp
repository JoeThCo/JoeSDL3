#pragma once

#include <SDL3/SDL.h>
#include "vector2.hpp"

class GameObject
{
protected:
    SDL_FRect rect;

public:
    GameObject(float x, float y, float w, float h);
    virtual ~GameObject() = default;

    virtual void update(float deltaTime, const bool *keystate = nullptr) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;

    SDL_FRect getRect() const;
};

class Player : public GameObject
{
private:
    float speed;

public:
    Player(float x, float y, float w, float h, float speed);

    void update(float deltaTime, const bool *keystate) override;
    void render(SDL_Renderer *renderer) override;
};