#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

/*
cmake --build --preset default
build/JoeGameEngine
*/

SDL_Window *window;
SDL_Renderer *renderer;

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
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int, char **)
{
    if (!init())
        return 1;

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderClear(renderer); // fill back buffer with draw call

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, 0, 0, 100, 100);

    SDL_FRect r;
    r.x = 200;
    r.y = 200;
    r.h = 50;
    r.w = 50;
    SDL_RenderRect(renderer, &r);

    SDL_RenderPresent(renderer); // display that hoe

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

        SDL_Delay(16);
    }

    kill();
    return 0;
}