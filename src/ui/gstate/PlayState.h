#pragma once

#include "engine/AsterGame.h"

#include "ui/Font.h"
#include "ui/TextControl.h"

#include "GameState.h"

namespace ui
{
class PlayState : public CGameState
{
public:
    // Implementation of specific events
    void OnKeyDown(SDL_KeyboardEvent& e);
    void OnKeyUp(SDL_KeyboardEvent& e);
    void OnResize(int cx, int cy);
    void Update(double TimeStep);
    void Draw();

    void Reset();
    bool IsGameOver(){return AsterGame.IsGameOver();}
    void EnterState();
    void LeaveState();
    // Returns the single instance
    static PlayState* GetInstance(StateManager* pManager);
protected:
    PlayState(StateManager* pManager);
private:
    // The font used to draw text
    ui::Font* m_pFontSmall;
    ui::Font* m_pFontLarge;
    TextControl* m_pGameOverText;
    ge::AsterGame AsterGame;
    bool m_bDispFPS;

    void Init();
    void Cleanup();
};
} // namespace ui
