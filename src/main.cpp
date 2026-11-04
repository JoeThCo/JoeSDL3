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
SDL_Surface *surface;

SDL_Surface *image1;

void printError()
{
    std::println("SDL Init Error: {}", SDL_GetError());
}

Uint32 makeColor(SDL_Surface *surface, int r, int g, int b)
{
    return SDL_MapRGB(
        SDL_GetPixelFormatDetails(surface->format),
        SDL_GetSurfacePalette(surface),
        r, g, b);
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
    window = SDL_CreateWindow("JoeGameEngine", 1280, 720, 0);
    if (!window)
    {
        printError();
        return false;
    }

    // get the window surface
    surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        printError();
        return false;
    }
    return true;
}

bool load()
{
    SDL_Surface *temp1;

    temp1 = SDL_LoadBMP("assets/CubeWorld.bmp");
    if (!temp1)
    {
        printError();
        return false;
    }

    image1 = SDL_ConvertSurface(temp1, surface->format);
    SDL_DestroySurface(temp1);

    if (!image1)
    {
        printError();
        return false;
    }

    return true;
}

void kill()
{
    SDL_DestroySurface(image1);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int, char **)
{
    if (!init())
        return 1;

    if (!load())
        return 1;

    Uint32 color = makeColor(surface, 128, 128, 128);
    SDL_FillSurfaceRect(surface, NULL, color);

    SDL_Rect dest;
    dest.x = 160;
    dest.y = 120;
    dest.w = 320;
    dest.h = 240;
    SDL_BlitSurfaceScaled(image1, NULL, surface, &dest, SDL_SCALEMODE_LINEAR);

    // update the window display
    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    bool is_main_looping = true;
    while (is_main_looping)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                is_main_looping = false;
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