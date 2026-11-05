#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "GameObject.hpp"

/*
cmake --build --preset default
build/JoeGameEngine
*/

SDL_Window *window;
SDL_Renderer *renderer;
Uint64 lastTime = SDL_GetTicks();

void printError()
{
    std::println("SDL Init Error: {}", SDL_GetError());
}

bool init()
{
    // INIT SDL, will return false if it fails
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        printError();
        return false;
    }

    // create the window
    bool isCreated = SDL_CreateWindowAndRenderer("JoeGameEngine", 1280, 720, 0, &window, &renderer);
    if (!isCreated)
    {
        printError();
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

    SDL_RenderPresent(renderer); // display that hoe

    auto player = std::make_unique<Player>(100.0f, 100.0f, 50.0f, 50.0f, 100.0f);

    SDL_Event event;
    bool isMainLooping = true;
    while (isMainLooping)
    {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event) != 0)
        {
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
            }
        }

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        const bool *keystate = SDL_GetKeyboardState(NULL);

        // update objects
        player->update(deltaTime, keystate);

        // render background
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer); // fill back buffer with draw call

        // render objects
        player->render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    kill();
    return 0;
}