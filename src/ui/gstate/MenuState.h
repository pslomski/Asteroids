#pragma once

#include "ui/GameFont.h"
#include "ui/TextControl.h"

#include "GameState.h"
#include "PlayState.h"

namespace ui
{
// Specialization of the CGameState class for 
// the menu state. This displays a menu in which
// the player can start a new game, continue an 
// existing game, see the high-scores or exit the game.
class CMenuState : public CGameState
{
public:
    void OnKeyDown(SDL_KeyboardEvent&);
    void Update(double TimeStep);
    void Draw();
    void EnterState();
    void LeaveState();
    static CMenuState* GetInstance(StateManager* pManager);

protected:
    CMenuState(StateManager* pManager);

private:
    using Font = ui::GameFont;
    void Init();
    void Cleanup();
    void SelectionUp();
    void SelectionDown();
    // The player validated the current selection
    void SelectionChosen();
    void ExitGame(void);

    Font* m_pFont;
    Font* m_pFontSmall;
    Font* m_pFontSmall2;
    Font* m_pFontLarge;
    // Index of the current selected menu item
    int m_iCurrentSelection;
    // A pointer to the current active game (if any).
    PlayState* m_pCurrentGame;

    // The text controls of the different entries.
    TextControl* m_pTitleText;
    TextControl* m_pNewGameText;
    TextControl* m_pResumeGameText;
    TextControl* m_pScoresText;
    TextControl* m_pExitText;
    TextControl* m_pOptionsText;
    TextControl* GetTextControl(int id);
    void SetBlinkText(int id, bool in_bBlink);
};
} // namespace ui
