#pragma once

#include <SDL.h>
#include "sdl/Window.hpp"
#include "sound/SoundEngine.hpp"

namespace sdl
{
class Application
{
public:
    Application(sound::SoundEngine& soundEngine);
    ~Application();

    static void quitApp()
    {
        canQuit = true;
    }
    void init(Window *window);
    void run();

private:
    void cleanup();
    void onEvent(SDL_Event* e);

    sound::SoundEngine& soundEngine;
    static bool canQuit;
    Window *window{nullptr};
};
}
