#include "StateManager.h"

namespace ui
{
StateManager::StateManager()
{}

StateManager::~StateManager()
{}

void StateManager::changeState(GameState* const newState)
{
    if (activeState)
    {
        activeState->leaveState();
    }
    activeState = newState;
    if (activeState)
    {
        activeState->enterState();
    }
}

GameState* StateManager::getActiveState() const
{
    return activeState;
}

void StateManager::onKeyDown(SDL_KeyboardEvent& e)
{
    if (activeState)
    {
        activeState->onKeyDown(e);
    }
}

void StateManager::onKeyUp(SDL_KeyboardEvent& e)
{
    if (activeState)
    {
        activeState->onKeyUp(e);
    }
}

void StateManager::onChar(char* c)
{
    if (activeState)
    {
        activeState->onChar(c);
    }
}

void StateManager::onResize(int cx, int cy)
{
    if (activeState)
    {
        activeState->onResize(cx, cy);
    }
}

void StateManager::update(double dwCurrentTime)
{
    if (activeState)
    {
        activeState->update(dwCurrentTime);
    }
}

void StateManager::draw()
{
    if (activeState)
    {
        activeState->draw();
    }
}
} // namespace ui
