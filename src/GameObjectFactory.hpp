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

    inline GameObject *spawnPlayer(std::vector<std::unique_ptr<GameObject>> &gameObjects, Vector2 pos)
    {
        auto player = std::make_unique<GameObject>();
        player->addComponent<TransformComponent>(pos, Vector2(50.0f));
        player->addComponent<BoxColliderComponent>(50.0f, 50.0f);
        player->addComponent<ShapeRendererComponent>(ShapeType::FilledRect, SDL_Color(0, 255, 0, 255));
        player->addComponent<PlayerMovementComponent>(150.0f);

        GameObject *rawPlayer = player.get();
        gameObjects.push_back(std::move(player));
        return rawPlayer;
    }

    inline GameObject *spawnBullet(std::vector<std::unique_ptr<GameObject>> &gameObjects, Vector2 pos, float speed)
    {
        auto bullet = std::make_unique<GameObject>();
        bullet->addComponent<TransformComponent>(pos, Vector2(50.0f));
        bullet->addComponent<BoxColliderComponent>(50.0f, 50.0f);
        bullet->addComponent<ShapeRendererComponent>(ShapeType::Circle, SDL_Color(255, 0, 0, 255));

        GameObject *rawBullet = bullet.get();
        gameObjects.push_back(std::move(bullet));
        return rawBullet;
    }
}