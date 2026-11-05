#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <typeindex>
#include "Component.hpp"

class GameObject
{
protected:
    std::vector<std::unique_ptr<Component>> components;
    bool isAlive = true;

public:
    virtual ~GameObject() = default;

    // Add component to object
    template <typename T, typename... Args>
    T &addComponent(Args &&...args)
    {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->Owner = this;
        T &ref = *comp;
        components.push_back(std::move(comp));
        return ref;
    }

    // get component by type
    template <typename T>
    T *getComponent()
    {
        for (auto &comp : components)
        {
            if (auto *target = dynamic_cast<T *>(comp.get()))
            {
                return target;
            }
        }
        return nullptr;
    }

    void update(float deltaTime, const bool *keystate = nullptr)
    {
        for (auto &comp : components)
        {
            comp->update(deltaTime);
        }
    }

    void render(SDL_Renderer *renderer)
    {
        for (auto &comp : components)
        {
            comp->render(renderer);
        }
    }

    bool GetIsAlive() const { return isAlive; };
    void destroy() { isAlive = false; };
};