#include "engine/World.h"
#include "engine/Renderer.h"

#include "ui/gstate/MenuState.h"

#include "Exception.h"
#include "SDLTools.h"
#include "SDLWindow.h"

SDLWindow::SDLWindow(int width, int height)
{
    //Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    fPtrWnd = SDL_CreateWindow("Asteroids remake",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (fPtrWnd == NULL)
        throw SDLException("SDL Window could not be created");

    //Create context
    fContext = SDL_GL_CreateContext(fPtrWnd);
    if (fContext == NULL)
        throw SDLException("OpenGL context could not be created");

    //Use Vsync
    if (SDL_GL_SetSwapInterval(1) < 0)
        throw SDLException("Warning: Unable to set VSync");

    InitGL();
    OnSize(width, height);
    fStateManager = new ui::StateManager;
    fStateManager->ChangeState(ui::CMenuState::GetInstance(fStateManager));
}

SDLWindow::~SDLWindow()
{
    SDL_DestroyWindow(fPtrWnd);
}

void SDLWindow::OnSize(GLsizei width, GLsizei height)
{
    geWorld.scrWidth = width;
    geWorld.scrHeight = height;
    ast::Renderer::setWindowSize(width, height);
}

void SDLWindow::InitGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void SDLWindow::Update(double time)
{
    fStateManager->Update(time);
}

void SDLWindow::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fStateManager->Draw();
    SDL_GL_SwapWindow(fPtrWnd);
}

void SDLWindow::OnEvent(SDL_Event* e)
{
    switch (e->type) {
    case SDL_WINDOWEVENT:
        handleWindowEvent(e);
        break;
    case SDL_KEYDOWN:
        fStateManager->OnKeyDown(*SDLTools::GetKbEvent(e));
        break;
    case SDL_KEYUP:
        fStateManager->OnKeyUp(*SDLTools::GetKbEvent(e));
        break;
    case SDL_TEXTINPUT:
        fStateManager->OnChar(SDLTools::GetTextInputEvent(e)->text);
        break;
    }
}

void SDLWindow::handleWindowEvent(SDL_Event* e)
{
    if (e->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        OnSize(e->window.data1, e->window.data2);
    }
}
