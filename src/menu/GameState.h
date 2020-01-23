#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "SDL.h"

namespace menu {

	class StateManager;

	// Base class for the different states of the game.
	class CGameState {
	public:
		// Constructor
		CGameState(StateManager* pManager);
		// Destructor
		virtual ~CGameState();

		// The different 'events' functions. Child classes can 
		// implement the ones in which they are interested in.
		virtual void OnKeyDown(SDL_KeyboardEvent&) {};
		virtual void OnKeyUp(SDL_KeyboardEvent&) {};
		virtual void OnChar(char* c) { }
		virtual void OnResize(int cx, int cy) { }
		virtual void Update(double TimeStep) { }
		virtual void Draw() { }

		// Functions called when the state is entered or left
		// (transition from/to another state).
		virtual void EnterState() { }
		virtual void LeaveState() { }

	protected:
		// Helper function to switch to a new active state.
		void ChangeState(CGameState* pNewState);

		// The state manager.
		StateManager* m_pStateManager;
	};

} // namespace menu

#endif  // _GAMESTATE_H_