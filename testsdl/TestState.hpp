#pragma once

#include "ui/Font.hpp"
#include "ui/TextControl.h"
#include "ui/gstate/GameState.h"

namespace ui
{
class TestState : public GameState
{
public:
    TestState(StateManager* pManager);

    void OnKeyDown(SDL_KeyboardEvent&);
    void Update(double TimeStep);
    void Draw();
    void EnterState();
    void LeaveState();

private:
    void Init();
    void Cleanup();
    void ExitGame(void);

    Font* font;
    TextControl* titleText;
};
} // namespace ui
