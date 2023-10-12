#pragma once

#include <SDL.h>
#include "ui/gstate/StateManager.h"

namespace sdl
{
class Window
{
public:
    static Window* create(ui::StateManager* stateManager, int width, int height)
    {
        return new Window(stateManager, width, height);
    }
    static void destroy(Window*& ptrWindow)
    {
        delete ptrWindow;
        ptrWindow = nullptr;
    }
    void update(double time);
    void draw();
    void onEvent(SDL_Event* e);

private:
    Window(ui::StateManager* stateManager, int width, int height);
    ~Window();
    void initGL();
    void onSize(int width, int height);
    void handleWindowEvent(SDL_Event* e);

    ui::StateManager* stateManager{nullptr};
    SDL_Window* window{nullptr};
    SDL_GLContext context{nullptr};
};
} // namespace sdl
