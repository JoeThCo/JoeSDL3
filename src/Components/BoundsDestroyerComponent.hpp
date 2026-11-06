#pragma once
#include "Component.hpp"
#include "TransformComponent.hpp"

class BoundsDestroyerComponent : public Component
{
private:
    TransformComponent *transform = nullptr;
    float windowWidth;
    float windowHeight;
    float margin;

public:
    BoundsDestroyerComponent(GameObject *owner, float width, float height, float margin = 50.0f)
        : windowWidth(width), windowHeight(height), margin(margin)
    {
        Owner = owner;
    }

    void update(float deltaTime) override
    {
        if (!transform && Owner)
        {
            transform = Owner->getComponent<TransformComponent>();
        }

        if (!transform || !Owner)
            return;

        if (transform->x < -margin || transform->x > windowWidth + margin ||
            transform->y < -margin || transform->y > windowHeight + margin)
        {
            Owner->destroy();
            std::println("Off screen!");
        }
    }
};