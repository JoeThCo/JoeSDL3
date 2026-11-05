#pragma once
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/PlayerMovementComponent.hpp"
#include "Components/BoxColliderComponent.hpp"
#include "Components/ShapeRendererComponent.hpp"

namespace GameObjectFactory
{

    inline void spawnPlayer(std::vector<std::unique_ptr<GameObject>> &gameObjects, float x, float y)
    {
        auto player = std::make_unique<GameObject>();
        player->addComponent<TransformComponent>(x, y, 50.0f, 50.0f);
        player->addComponent<PlayerMovementComponent>(150.0f);
        player->addComponent<BoxColliderComponent>(50.0f, 50.0f);
        player->addComponent<ShapeRendererComponent>(0, 255, 0);
        gameObjects.push_back(std::move(player));
    }
}