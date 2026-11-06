#pragma once
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/PlayerMovementComponent.hpp"
#include "Components/BoxColliderComponent.hpp"
#include "Components/ShapeRendererComponent.hpp"
#include "Components/LinearRigidbody.hpp"
#include "Components/BoundsDestroyerComponent.hpp"
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

    inline GameObject *spawnBullet(std::vector<std::unique_ptr<GameObject>> &gameObjects, SDL_Window *window, Vector2 pos)
    {
        auto bullet = std::make_unique<GameObject>();

        float size = 15.0f;
        bullet->addComponent<TransformComponent>(pos, Vector2(size));
        bullet->addComponent<BoxColliderComponent>(size, size);
        bullet->addComponent<ShapeRendererComponent>(ShapeType::Circle, SDL_Color(255, 0, 0, 255));
        bullet->addComponent<LinearRigidBody>(bullet.get());

        int w = 0;
        int h = 0;
        SDL_GetWindowSize(window, &w, &h);
        bullet->addComponent<BoundsDestroyerComponent>(bullet.get(), w, h);

        GameObject *rawBullet = bullet.get();
        gameObjects.push_back(std::move(bullet));
        return rawBullet;
    }
}