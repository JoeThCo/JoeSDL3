#pragma once
#include <SDL3/SDL.h>
#include "GameObject.hpp"

class GameObject;

class Component
{
public:
    GameObject *Owner;
    virtual ~Component() = default;
    virtual void update(float deltaTime) {}
    virtual void render(SDL_Renderer *renderer) {}
};