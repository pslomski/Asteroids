#pragma once

#include "GameState.h"

namespace ui
{
// Manages different states of the game.
class StateManager
{
public:
    StateManager();
    ~StateManager();

    void onKeyDown(SDL_KeyboardEvent& e);
    void onKeyUp(SDL_KeyboardEvent& e);
    void onChar(char* c);
    void onResize(int cx, int cy);
    void update(double timeStep);
    void draw();

    void changeState(GameState* const newState);
    GameState* getActiveState() const;
private:
    GameState* activeState{nullptr};
};
} // namespace ui
