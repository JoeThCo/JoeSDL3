#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Collision.hpp"

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

    // create the window
    bool isCreated = SDL_CreateWindowAndRenderer("JoeGameEngine", 1280, 720, 0, &window, &renderer);
    if (!isCreated)
    {
        std::println("SDL Init Error: {}", SDL_GetError());
        return false;
    }
    return true;
}

void kill()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int, char **)
{
    if (!init())
        return 1;

    std::vector<std::unique_ptr<GameObject>> allGameObjects;

    allGameObjects.push_back(std::make_unique<Player>(200.0f, 200.0f, 50.0f, 50.0f, 100.0f));
    allGameObjects.push_back(std::make_unique<Wall>(100.0f, 100.0f, 50.0f, 50.0f));

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
                float mouseX, mouseY = 0.0f;
                SDL_GetMouseState(&mouseX, &mouseY);
                std::println("Mouse @ {}, {}", mouseX, mouseY);
                allGameObjects.push_back(std::make_unique<Player>(mouseX, mouseY, 50.0f, 50.0f, 100.0f));
            }
        }

        // delta time
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // key state
        const bool *keystate = SDL_GetKeyboardState(NULL);

        // update objects
        for (auto &gameObject : allGameObjects)
        {
            gameObject->update(deltaTime, keystate);
        }

        // collision
        for (size_t i = 0; i < allGameObjects.size(); ++i)
        {
            for (size_t j = i + 1; j < allGameObjects.size(); ++j)
            {
                if (!allGameObjects[i]->GetIsAlive() || !allGameObjects[j]->GetIsAlive())
                    continue;
                if (checkAABB(allGameObjects[i]->getRect(), allGameObjects[j]->getRect()))
                {
                }
            }
        }

        // render background
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer); // fill back buffer with draw call

        // render objects
        for (auto &gameObject : allGameObjects)
        {
            gameObject->render(renderer);
        }

        SDL_RenderPresent(renderer);

        // delete dead
        std::erase_if(allGameObjects, [](const auto &obj)
                      { return !obj->GetIsAlive(); });

        SDL_Delay(16);
    }

    kill();
    return 0;
}