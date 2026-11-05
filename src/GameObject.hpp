#pragma once

#include <SDL3/SDL.h>
#include "Vector2.hpp"

class GameObject
{
protected:
    SDL_FRect rect;
    bool isAlive = true;

public:
    GameObject(float x, float y, float w, float h);
    virtual ~GameObject();

    virtual void update(float deltaTime, const bool *keystate = nullptr) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;

    bool GetIsAlive() const { return isAlive; }
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