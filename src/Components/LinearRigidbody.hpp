#pragma once
#include "Component.hpp"
#include "../Vector2.hpp"
#include "TransformComponent.hpp"

class LinearRigidBody : public Component
{
private:
    TransformComponent *transform = nullptr;

public:
    Vector2 velocity;

    LinearRigidBody(GameObject *owner)
    {
        Owner = owner;
        if (Owner)
        {
            transform = Owner->getComponent<TransformComponent>();
        }
    }

    void update(float deltaTime) override
    {
        if (!transform)
            return;

        transform->x += velocity.x * deltaTime;
        transform->y += velocity.y * deltaTime;
    }

    void setVelocity(Vector2 v)
    {
        velocity = v;
    }

    void setVelocity(Vector2 dir, float speed)
    {
        setVelocity(dir * speed);
    }

    void setVelocityFromDirection(Vector2 dir, float speed)
    {
        float length = dir.magnitude();
        if (length > 0.0f)
        {
            velocity.x = (dir.x / length);
            velocity.y = (dir.y / length);
        }
        else
        {
            velocity.x = 0;
            velocity.y = 0;
        }
    }
};