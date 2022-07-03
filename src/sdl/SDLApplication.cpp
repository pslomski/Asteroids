#include <algorithm>
#include <SDL_ttf.h>
#include "Exception.h"
#include "engine/Tools.h"
#include "engine/World.h"
#include "engine/Sound.h"
#include "sdl/SDLApplication.h"
#include "sdl/SDLWindow.h"
#include "ui/gstate/MenuState.h"

bool SDLApplication::canQuit = false;

SDLApplication::SDLApplication()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw SDLException("SDL library initialization failed");
    }
    if (TTF_Init() < 0)
    {
        throw SDLException("Could not initialize SDL2_ttf");
    }
    geSound.Open();
    geMusic.Open();
}

SDLApplication::~SDLApplication()
{
    cleanup();
}

void SDLApplication::cleanup()
{
    geMusic.Close();
    geSound.Close();
    TTF_Quit();
    SDL_Quit();
    SDLWindow::destroy(window);
}

void SDLApplication::init(SDLWindow *window)
{
    this->window = window;
}

int GetVRefersh()
{
    constexpr int DEFAULT_VREFRESH = 60;
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) == 0)
    {
        return mode.refresh_rate;
    }
    else
    {
        return DEFAULT_VREFRESH;
    }
}

void SDLApplication::run()
{
    int VRefresh = GetVRefersh();
    Float FRAME_TIME = (1000.0 / VRefresh);
    DWORD Sleep = int(FRAME_TIME) - 1;
    Float dt = 0.0; // last update time
    Float lastUpdateTime = geWorld.GetCurrentTime();
    Float accumulator = 0.0;
    const Float TIME_STEP = 1.0 / VRefresh; // Time span of physics frame and screen refresh.
    const Float MAX_ACCUMULATED_TIME = 1.0;

    SDL_Event e;
    while (!canQuit)
    {
        while (SDL_PollEvent(&e))
        {
            onEvent(&e);
        }
        dt = geWorld.GetCurrentTime() - lastUpdateTime; // Time elapsed since the last frame
        lastUpdateTime += dt;
        dt = std::max((Float)0, dt);
        accumulator += dt;
        accumulator = std::ranges::clamp(accumulator, 0.0, MAX_ACCUMULATED_TIME);
        bool bUpdate = false;
        while (accumulator > TIME_STEP)
        {
            geWorld.dt = TIME_STEP;
            window->update(TIME_STEP);
            accumulator -= TIME_STEP;
            bUpdate = true;
        }
        geWorld.interp = accumulator / TIME_STEP;
        window->draw();
    }
}

void SDLApplication::onEvent(SDL_Event* e)
{
    switch (e->type)
    {
    case SDL_QUIT:
        quitApp();
        break;
    default:
        window->onEvent(e);
    }
}
