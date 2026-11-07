#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <memory>
#include <print>

#include "GameObjectFactory.hpp"
#include "GameObject.hpp"

/*
cmake --build --preset default
build/JoeGameEngine
*/

// look at https://examples.libsdl.org/SDL3/renderer/05-rectangles/

SDL_Window *window;
SDL_Renderer *renderer;
Uint64 lastTime;

std::vector<std::unique_ptr<GameObject>> allGameObjects;
GameObject *player = NULL;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    // INIT SDL, will return false if it fails
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // font initing
    if (!TTF_Init())
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    // window init
    if (!SDL_CreateWindowAndRenderer("JoeGameEngine", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    // somewhere else? "Ready" func?
    player = GameObjectFactory::spawnPlayer(allGameObjects, Vector2(100.0f, 100.0f));

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_UP:
    case SDL_EVENT_KEY_DOWN:
    {
        const char *key_char = SDL_GetKeyName(event->key.key);
        std::string_view action = (event->type == SDL_EVENT_KEY_DOWN) ? "down" : "up";
        // std::println("{} {}", key_char, action);
        return SDL_APP_CONTINUE;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    {
        Vector2 mousePosition = Vector2(event->button.x, event->button.y);
        Vector2 spawnPosition = Vector2(0, 0);

        if (auto *playerTransform = player->getComponent<TransformComponent>())
        {
            spawnPosition = playerTransform->getPosition() + (playerTransform->getSize() * 0.5f);
        }

        Vector2 direction = mousePosition - spawnPosition;

        GameObject *bullet = GameObjectFactory::spawnBullet(allGameObjects, window, spawnPosition);
        if (auto *rigidbody = bullet->getComponent<LinearRigidBody>())
        {
            rigidbody->setVelocity(direction.normalized(), 300);
        }
        return SDL_APP_CONTINUE;
    }
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // 1) delta time
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // 2) key state
    // use the event in the gameobject/component?
    const bool *keystate = SDL_GetKeyboardState(NULL);

    // update objects
    for (auto &gameObject : allGameObjects)
    {
        if (!gameObject->GetIsAlive())
            continue;
        gameObject->update(deltaTime, keystate);
    }

    // collision
    // for (size_t i = 0; i < allGameObjects.size(); ++i)
    // {
    //     auto *colliderA = allGameObjects[i]->getComponent<BoxColliderComponent>();
    //     if (!colliderA || !allGameObjects[i]->GetIsAlive())
    //         continue;

    //     for (size_t j = i + 1; j < allGameObjects.size(); ++j)
    //     {
    //         auto *colliderB = allGameObjects[j]->getComponent<BoxColliderComponent>();
    //         if (!colliderB || !allGameObjects[j]->GetIsAlive())
    //             continue;

    //         // Use your inline checkAABB function with the component's rects
    //         if (checkAABB(colliderA->getRect(), colliderB->getRect()))
    //         {
    //             // Collision occurred between object i and object j!
    //         }
    //     }
    // }

    // delete dead
    std::erase_if(allGameObjects, [](const auto &obj)
                  { return !obj->GetIsAlive(); });

    // render background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // fill back buffer with draw call

    // render
    for (auto &gameObject : allGameObjects)
    {
        if (!gameObject->GetIsAlive())
            continue;
        gameObject->render(renderer);
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TTF_Quit(); // shuts down extension libraries/core sdl
    SDL_Quit();
}