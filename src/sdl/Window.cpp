#include "aster/World.h"
#include "gl/Renderer.hpp"
#include "sdl/Exception.hpp"
#include "sdl/SDLTools.h"
#include "sdl/Window.hpp"

namespace sdl
{
Window::Window(ui::StateManager* stateManager, int width, int height)
{
    this->stateManager = stateManager;
    //Use OpenGL 2.1
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow("Asteroids remake",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        throw SDLException("SDL Window could not be created");
    }
    context = SDL_GL_CreateContext(window);
    if (context == nullptr)
    {
        throw SDLException("OpenGL context could not be created");
    }
    initGL();
    onSize(width, height);
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}

void Window::onSize(int width, int height)
{
    geWorld.scrWidth = width;
    geWorld.scrHeight = height;
    gl::Renderer::setWindowSize(width, height);
}

void Window::initGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Window::update(double time)
{
    stateManager->update(time);
}

void Window::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    stateManager->draw();
    SDL_GL_SwapWindow(window);
}

void Window::onEvent(SDL_Event* e)
{
    switch (e->type) {
    case SDL_WINDOWEVENT:
        handleWindowEvent(e);
        break;
    case SDL_KEYDOWN:
        stateManager->onKeyDown(*SDLTools::GetKbEvent(e));
        break;
    case SDL_KEYUP:
        stateManager->onKeyUp(*SDLTools::GetKbEvent(e));
        break;
    case SDL_TEXTINPUT:
        stateManager->onChar(SDLTools::GetTextInputEvent(e)->text);
        break;
    }
}

void Window::handleWindowEvent(SDL_Event* e)
{
    if (e->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        onSize(e->window.data1, e->window.data2);
    }
}
}
