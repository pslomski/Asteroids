#pragma once

#include "ui/Font.h"
#include "ui/TextControl.h"
#include "ui/gstate/GameState.h"

namespace ui
{
class OptionsState : public CGameState{
public:
    void OnKeyDown(SDL_KeyboardEvent& e);
    void Update(double TimeStep);
    void Draw();
    void EnterState();
    void LeaveState();
    static OptionsState* GetInstance(StateManager* pManager);

protected:
    OptionsState(StateManager* pManager);
private:
    int mCurrentSelection;
    Font* mFont;
    TextControl* mTitleText;
    TextControl* mMusicVolText;
    TextControl* mSoundVolText;

    void Init();
    void Cleanup();
    void SelectionUp();
    void SelectionDown();
    void LeftArrow();
    void RightArrow();
    TextControl* GetTextControl(int id);
    void SetBlinkText(int id, bool isBlink);
};
} // namespace ui
