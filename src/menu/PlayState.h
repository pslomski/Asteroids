#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameState.h"
#include "GameFont.h"
#include "../engine/AsterGame.h"
#include "TextControl.h"

namespace menu{

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
	ast::GameFont* m_pFontSmall;
	ast::GameFont* m_pFontLarge;
	CTextControl* m_pGameOverText;
	ge::AsterGame AsterGame;
	bool m_bDispFPS;

	void Init();
	void Cleanup();
};

}//namespace menu

#endif  // _PLAYSTATE_H_