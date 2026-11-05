#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>

#include "GameObject.hpp"
#include "Collision.hpp"
#include "Components/BoxColliderComponent.hpp"
#include "Components/ShapeRendererComponent.hpp"
#include "Components/PlayerMovementComponent.hpp"

/*
cmake --build --preset default
build/JoeGameEngine
*/

SDL_Window *window;
SDL_Renderer *renderer;
Uint64 lastTime = SDL_GetTicks();

bool init()
{
    // INIT SDL, will return false if it fails
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        return false;
    }

    // font initing
    if (!TTF_Init())
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // window init
    bool isCreated = SDL_CreateWindowAndRenderer("JoeGameEngine", 1280, 720, 0, &window, &renderer);
    if (!isCreated)
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    return true;
}

void kill()
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

void spawnPlayer(std::vector<std::unique_ptr<GameObject>> &allGameObjects, float startX, float startY)
{
    auto player = std::make_unique<GameObject>();
    player->addComponent<TransformComponent>(startX, startY, 50.0f, 100.0f);
    player->addComponent<PlayerMovementComponent>(150.0);
    player->addComponent<BoxColliderComponent>(50.0f, 50.0f);
    player->addComponent<ShapeRendererComponent>(0, 255, 0);
    allGameObjects.push_back(std::move(player));
}

int main(int, char **)
{
    if (!init())
        return 1;

    std::vector<std::unique_ptr<GameObject>> allGameObjects;

    spawnPlayer(allGameObjects, 100.0f, 100.0f);

    SDL_Event event;
    bool isMainLooping = true;
    while (isMainLooping)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            // basic input
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                isMainLooping = false;
                break;
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
            {
                char key_char = static_cast<char>(event.key.key);
                std::string_view action = (event.type == SDL_EVENT_KEY_DOWN) ? "down" : "up";
                std::println("{} {}", key_char, action);
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                float mouseX = 0.0f;
                float mouseY = 0.0f;
                SDL_GetMouseState(&mouseX, &mouseY);
                std::println("Mouse @ {}, {}", mouseX, mouseY);
                // allGameObjects.push_back(std::make_unique<Player>(mouseX, mouseY, 50.0f, 50.0f, 100.0f));
            }
        }

        // 1) delta time
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // 2) key state
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

        // render background
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer); // fill back buffer with draw call

        // delete dead
        std::erase_if(allGameObjects, [](const auto &obj)
                      { return !obj->GetIsAlive(); });

        // render
        for (auto &gameObject : allGameObjects)
        {
            if (!gameObject->GetIsAlive())
                continue;
            gameObject->render(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    kill();
    return 0;
}