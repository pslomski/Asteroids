#include <assert.h>
#include "../SDLTools.h"
#include "MenuState.h"
#include "HighScoreState.h"
#include "../Menu/OptionsState.h"
#include "PlayState.h"
#include "StateManager.h"
#include "../engine/World.h"
#include "../engine/Consts.h"
#include "../engine/renderer.h"
#include "../SDLApplication.h"

namespace menu {

	CMenuState::CMenuState(StateManager* pManager)
		: CGameState(pManager), m_pFont(NULL), m_iCurrentSelection(0),
		m_pCurrentGame(NULL)
	{
	}

	void CMenuState::Init()
	{
		m_pFont = new ast::GameFont("vector battle", 20);
		m_pFontSmall = new ast::GameFont("vector battle", 15);
		m_pFontLarge = new ast::GameFont("vector battle", 40);
		m_pFontSmall2 = new ast::GameFont("vector battle", 10);

		int dy = int(1.0 / 12.0 * geWorld.scrHeight);
		int left = int(1.0 / 4.0 * geWorld.scrWidth);
		int right = int(3.0 / 4.0 * geWorld.scrWidth);
		int top = int(1.0 / 4.5 * geWorld.scrHeight);
		int bottom = top + dy;

		m_pTitleText = new CTextControl(m_pFontLarge, ast::Rectanglei(0, top, 0, geWorld.scrWidth));
		m_pTitleText->SetAlignement(CTextControl::taCenter);
		m_pTitleText->SetText("Asteroids 2010");

		m_pNewGameText = new CTextControl(m_pFont, ast::Rectanglei(top, bottom, left, right));
		m_pNewGameText->SetAlignement(CTextControl::taCenter);
		m_pNewGameText->SetText("New game");

		top += dy; bottom += dy;
		m_pResumeGameText = new CTextControl(m_pFont, ast::Rectanglei(top, bottom, left, right));
		m_pResumeGameText->SetAlignement(CTextControl::taCenter);
		m_pResumeGameText->SetText("Resume game");

		top += dy; bottom += dy;
		m_pOptionsText = new CTextControl(m_pFont, ast::Rectanglei(top, bottom, left, right));
		m_pOptionsText->SetAlignement(CTextControl::taCenter);
		m_pOptionsText->SetText("Settings");

		top += dy; bottom += dy;
		m_pScoresText = new CTextControl(m_pFont, ast::Rectanglei(top, bottom, left, right));
		m_pScoresText->SetAlignement(CTextControl::taCenter);
		m_pScoresText->SetText("High scores");

		top += dy; bottom += dy;
		m_pExitText = new CTextControl(m_pFont, ast::Rectanglei(top, bottom, left, right));
		m_pExitText->SetAlignement(CTextControl::taCenter);
		m_pExitText->SetText("Exit");
	}

	void CMenuState::Cleanup()
	{
		delete m_pFont;
		delete m_pFontSmall;
		delete m_pFontSmall2;
		delete m_pFontLarge;
		delete m_pNewGameText;
		delete m_pResumeGameText;
		delete m_pScoresText;
		delete m_pExitText;
		delete m_pOptionsText;

		m_pFontSmall = NULL;
		m_pFontSmall2 = NULL;
		m_pFontLarge = NULL;
		m_pNewGameText = NULL;
		m_pResumeGameText = NULL;
		m_pScoresText = NULL;
		m_pExitText = NULL;
		m_pOptionsText = NULL;
	}

	void CMenuState::EnterState()
	{
		Init();
		SetBlinkText(m_iCurrentSelection, false);
		if (!m_pCurrentGame || m_pCurrentGame->IsGameOver()) {
			if (1 == m_iCurrentSelection)
				m_iCurrentSelection = 0;
			m_pResumeGameText->SetTextColor(0.3f, 0.3f, 0.3f);
		}
		else {
			m_pResumeGameText->SetTextColor(1.0f, 1.0f, 1.0f);
		}
		SetBlinkText(m_iCurrentSelection, true);
	}

	void CMenuState::LeaveState()
	{
		Cleanup();
	}

	CMenuState* CMenuState::GetInstance(StateManager* pManager)
	{
		static CMenuState Instance(pManager);
		return &Instance;
	}

	void CMenuState::OnKeyDown(SDL_KeyboardEvent& e)
	{
		switch (SDLTools::GetKeycode(e))
		{
		case SDLK_DOWN:
			SelectionDown();
			break;
		case SDLK_UP:
			SelectionUp();
			break;
		case SDLK_RETURN:
			SelectionChosen();
			break;
		case SDLK_ESCAPE:
			ExitGame();
			break;
		}
	}

	void CMenuState::Update(double TimeStep)
	{
		CTextControl* pTxtCtrl = GetTextControl(m_iCurrentSelection);
		if (pTxtCtrl) pTxtCtrl->Update(TimeStep);
	}

	void CMenuState::Draw()
	{
		//auto dm = ast::DrawMode2DText();
		glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
		glLoadIdentity();			 // Reset The Projection Matrix
		glOrtho(0, geWorld.scrWidth, geWorld.scrHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);	 // Select The Modelview Matrix
		glLoadIdentity();			 // Reset The Modelview Matrix
		
		m_pTitleText->Draw();
		m_pNewGameText->Draw();
		m_pResumeGameText->Draw();
		m_pOptionsText->Draw();
		m_pScoresText->Draw();
		m_pExitText->Draw();

		CTextControl txtControls(m_pFontSmall2, ast::Rectanglei(int(0.7 * geWorld.scrHeight), int(0.7 * geWorld.scrHeight + 20), 0, geWorld.scrWidth));
		txtControls.SetAlignement(CTextControl::taCenter);
		txtControls.SetTextColor(0.8f, 0.8f, 0.8f);
		txtControls.SetText("Controls:");
		txtControls.Draw();
		txtControls.Position.offsetRect(0, 20);
		txtControls.SetText("left arrow - turn left, right arrow - turn right");
		txtControls.Draw();
		txtControls.Position.offsetRect(0, 20);
		txtControls.SetText("up arrow - forward, space - fire");
		txtControls.Draw();

		CTextControl line(m_pFontSmall, ast::Rectanglei(geWorld.scrHeight - 100, geWorld.scrHeight - 50, 0, geWorld.scrWidth));
		line.SetAlignement(CTextControl::taCenter);
		line.SetTextColor(0.7f, 0.7f, 0.7f);
		line.SetText("Asteroids remake by Piotr Slomski");
		line.Draw();
	}

	CTextControl* CMenuState::GetTextControl(int id)
	{
		switch (id) {
		case 0: return m_pNewGameText; break;
		case 1: return m_pResumeGameText; break;
		case 2: return m_pOptionsText; break;
		case 3: return m_pScoresText; break;
		case 4: return m_pExitText; break;
		}
		assert(NULL);
		return NULL;
	}

	void CMenuState::SetBlinkText(int id, bool in_bBlink)
	{
		CTextControl* pTxtCtrl = GetTextControl(m_iCurrentSelection);
		if (pTxtCtrl) pTxtCtrl->SetBlink(in_bBlink);
	}

	void CMenuState::SelectionUp()
	{
		SetBlinkText(m_iCurrentSelection, false);
		m_iCurrentSelection--;
		if (m_iCurrentSelection == -1)
			m_iCurrentSelection = 4;

		// If there is no current game, we should skip
		// the "Resume game" item.
		if (m_iCurrentSelection == 1)
		{
			if (!m_pCurrentGame || m_pCurrentGame->IsGameOver())
				m_iCurrentSelection--;
		}
		SetBlinkText(m_iCurrentSelection, true);
	}

	void CMenuState::SelectionDown()
	{
		SetBlinkText(m_iCurrentSelection, false);
		m_iCurrentSelection++;
		if (m_iCurrentSelection == 5)
			m_iCurrentSelection = 0;

		// If there is no current game, we should skip
		// the "Resume game" item.
		if (m_iCurrentSelection == 1)
		{
			if (!m_pCurrentGame || m_pCurrentGame->IsGameOver())
				m_iCurrentSelection++;
		}
		SetBlinkText(m_iCurrentSelection, true);
	}

	void CMenuState::SelectionChosen()
	{
		switch (m_iCurrentSelection)
		{
		case 0:
			if (!m_pCurrentGame)
				m_pCurrentGame = PlayState::GetInstance(m_pStateManager);
			m_pCurrentGame->Reset();
			SetBlinkText(m_iCurrentSelection, false);
			m_iCurrentSelection = 1;
			SetBlinkText(m_iCurrentSelection, true);
			ChangeState(m_pCurrentGame);
			break;

		case 1:
			if (m_pCurrentGame && !m_pCurrentGame->IsGameOver())
				ChangeState(m_pCurrentGame);
			break;

		case 2:
			ChangeState(OptionsState::GetInstance(m_pStateManager));
			break;

		case 3:
			ChangeState(HighScoreState::GetInstance(m_pStateManager));
			break;

		case 4:
			SDLApplication::QuitApp();
			break;
		}
	}

	void CMenuState::ExitGame(void)
	{
		SDLApplication::QuitApp();
	}

}//namespace menu