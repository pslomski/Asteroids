#pragma once

#include <SDL.h>

namespace ui
{
class StateManager;

// Base class for the different states of the game.
class GameState
{
public:
    GameState(StateManager* const manager);
    virtual ~GameState();

    virtual void onKeyDown(SDL_KeyboardEvent&) {}
    virtual void onKeyUp(SDL_KeyboardEvent&) {}
    virtual void onChar(char* c) {}
    virtual void onResize(int cx, int cy) {}
    virtual void update(double TimeStep) {}
    virtual void draw() {}
    virtual void enterState() {}
    virtual void leaveState() {}

protected:
    void changeState(GameState* const newState) const;

    StateManager* const stateManager;
};
} // namespace ui
