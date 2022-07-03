#pragma once

#include <SDL.h>
#include "sdl/SDLWindow.h"

class SDLApplication
{
public:
    SDLApplication();
    ~SDLApplication();
    static void quitApp()
    {
        canQuit = true;
    }
    void init(SDLWindow *window);
    void run();

private:
    void cleanup();
    void onEvent(SDL_Event* e);

    static bool canQuit;
    SDLWindow *window;
};
