#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include "GameState.h"
#include "GameFont.h"
#include "PlayState.h"
#include "TextControl.h"

namespace menu {

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
		void Init();
		void Cleanup();
		void SelectionUp();
		void SelectionDown();
		// The player validated the current selection
		void SelectionChosen();
		void ExitGame(void);

		ast::GameFont* m_pFont;
		ast::GameFont* m_pFontSmall;
		ast::GameFont* m_pFontSmall2;
		ast::GameFont* m_pFontLarge;
		// Index of the current selected menu item
		int m_iCurrentSelection;
		// A pointer to the current active game (if any).
		PlayState* m_pCurrentGame;

		// The text controls of the different entries.
		CTextControl* m_pTitleText;
		CTextControl* m_pNewGameText;
		CTextControl* m_pResumeGameText;
		CTextControl* m_pScoresText;
		CTextControl* m_pExitText;
		CTextControl* m_pOptionsText;
		CTextControl* GetTextControl(int id);
		void SetBlinkText(int id, bool in_bBlink);
	};

} // namespace menu

#endif  // _MENUSTATE_H_