#pragma once
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/PlayerMovementComponent.hpp"
#include "Components/BoxColliderComponent.hpp"
#include "Components/ShapeRendererComponent.hpp"
#include "Vector2.hpp"

namespace GameObjectFactory
{

    inline void spawnPlayer(std::vector<std::unique_ptr<GameObject>> &gameObjects, Vector2 pos)
    {
        auto player = std::make_unique<GameObject>();
        player->addComponent<TransformComponent>(pos.x, pos.y, 50.0f, 50.0f);
        player->addComponent<PlayerMovementComponent>(150.0f);
        player->addComponent<BoxColliderComponent>(50.0f, 50.0f);
        player->addComponent<ShapeRendererComponent>(0, 255, 0);
        gameObjects.push_back(std::move(player));
    }

    inline void spawnBullet(std::vector<std::unique_ptr<GameObject>> &gameObjects, Vector2 pos, float speed) {}
}