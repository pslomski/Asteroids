#pragma once

#include <SDL.h>
#include "sdl/Window.hpp"

namespace sdl
{
class Application
{
public:
    Application();
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

    static bool canQuit;
    Window *window;
};
}
