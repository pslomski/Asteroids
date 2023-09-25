#include "Application.hpp"

#include <algorithm>
#include <SDL_ttf.h>

#include "Exception.hpp"
#include "Window.hpp"
#include "aster/Tools.h"
#include "aster/World.h"
#include "log/Log.hpp"
#include "sound/Sound.hpp"
#include "sound/SoundEngine.hpp"
#include "ui/gstate/MenuState.h"

namespace sdl
{
bool Application::canQuit = false;

Application::Application(sound::SoundEngine& soundEngine) :
    soundEngine{soundEngine}
{
    LOG_INF("Application::Application window: %p", window);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw SDLException("SDL library initialization failed");
    }
    if (TTF_Init() < 0)
    {
        throw SDLException("Could not initialize SDL2_ttf");
    }
    sound::geSound.Open();
    sound::geMusic.Open();
}

Application::~Application()
{
    LOG_INF("Application::~Application window: %p", window);
    cleanup();
}

void Application::cleanup()
{
    sound::geMusic.Close();
    sound::geSound.Close();
    TTF_Quit();
    SDL_Quit();
    Window::destroy(window);
}

void Application::init(Window *window)
{
    this->window = window;
}

int getVRefersh()
{
    constexpr int defaultVRefresh{60};
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) == 0)
    {
        return mode.refresh_rate;
    }
    else
    {
        return defaultVRefresh;
    }
}

void Application::run()
{
    constexpr Float accumulatedTimeMax{1.0};
    const int vRefresh{getVRefersh()};
    const Float timeStep{1.0 / vRefresh}; // Time span of physics frame and screen refresh.
    const Float frameTime{1000.0 / vRefresh};
    Float lastUpdateTime{geWorld.getCurrentTime()};
    Float accumulator{0.0};
    Float dt; // last update time
    while (!canQuit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            onEvent(&e);
        }
        dt = geWorld.getCurrentTime() - lastUpdateTime; // Time elapsed since the last frame
        lastUpdateTime += dt;
        dt = std::max(static_cast<Float>(0.0), dt);
        accumulator += dt;
        accumulator = std::ranges::clamp(accumulator, 0.0, accumulatedTimeMax);
        bool isUpdate{false};
        while (accumulator > timeStep)
        {
            geWorld.dt = timeStep;
            window->update(timeStep);
            accumulator -= timeStep;
            isUpdate = true;
        }
        geWorld.interp = accumulator / timeStep;
        window->draw();
    }
}

void Application::onEvent(SDL_Event* e)
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
}
