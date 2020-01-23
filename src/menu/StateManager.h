#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "GameState.h"

namespace menu{

// Manages the different states of the game.
class StateManager
{
public:
	StateManager();
	~StateManager();

	// Switches to another active state.
	void ChangeState(CGameState* pNewState)
	{
		if (m_pActiveState)
			m_pActiveState->LeaveState();
		m_pActiveState = pNewState;
		m_pActiveState->EnterState();
	}

	// Returns the current active state.
	CGameState* GetActiveState()  { return m_pActiveState; }

	// 'Events' function, they are simply redirected to
	// the active state.
	void OnKeyDown(SDL_KeyboardEvent& e);
	void OnKeyUp(SDL_KeyboardEvent& e);
	void OnChar(char* c);
	void OnResize(int cx, int cy);
	void Update(double TimeStep);
	void Draw();

private:
	// Active State of the game (intro, play, ...)
	CGameState* m_pActiveState;
};

}//namespace menu

#endif  // _STATEMANAGER_H_