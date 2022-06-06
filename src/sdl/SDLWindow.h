#pragma once

#include <SDL.h>
#include <GL/gl.h>

#include "ui/gstate/StateManager.h"

class SDLWindow {
private:
    ui::StateManager* fStateManager;
    SDL_Window* fPtrWnd = NULL;
    SDL_GLContext fContext;

    SDLWindow(int width, int height);
    ~SDLWindow();

    void InitGL();
    void OnSize(GLsizei width, GLsizei height);
    void handleWindowEvent(SDL_Event* e);
public:
    static SDLWindow* Create(int width, int height)
    {
        return new SDLWindow(width, height);
    }
    static void Destroy(SDLWindow* &ptrWindow)
    {
        delete ptrWindow;
        ptrWindow = NULL;
    }
    void Update(double time);
    void Draw();
    void OnEvent(SDL_Event* e);
};
