#include "GameState.h"
#include "StateManager.h"

namespace ui
{
GameState::GameState(StateManager* const manager) : stateManager(manager) {}

GameState::~GameState() {}

void GameState::changeState(GameState* const newState) const
{
    stateManager->changeState(newState);
}
} // namespace ui
