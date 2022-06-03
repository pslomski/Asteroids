#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "SDLWindow.h"

class SDLApplication
{
private:
    static bool fQuit;
    SDLWindow *fPtrWnd;
    void OnEvent(SDL_Event* e);
public:
    static void QuitApp() { fQuit = true; }
    void Init();
    void Run();
    void Cleanup();
};
