#pragma once

#include <SDL.h>
#include "ui/gstate/StateManager.h"

class SDLWindow
{
public:
    static SDLWindow* create(ui::StateManager* stateManager, int width, int height)
    {
        return new SDLWindow(stateManager, width, height);
    }
    static void destroy(SDLWindow* &ptrWindow)
    {
        delete ptrWindow;
        ptrWindow = nullptr;
    }
    void update(double time);
    void draw();
    void onEvent(SDL_Event* e);

private:
    SDLWindow(ui::StateManager* stateManager, int width, int height);
    ~SDLWindow();
    void initGL();
    void onSize(int width, int height);
    void handleWindowEvent(SDL_Event* e);

    ui::StateManager* stateManager{nullptr};
    SDL_Window* window{nullptr};
    SDL_GLContext context{nullptr};
};
