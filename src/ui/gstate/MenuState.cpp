#include <assert.h>

#include "engine/World.h"
#include "engine/Consts.h"
#include "engine/renderer.h"
#include "sdl/SDLApplication.h"
#include "sdl/SDLTools.h"

#include "HighScoreState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "PlayState.h"
#include "StateManager.h"

namespace ui
{
CMenuState::CMenuState(StateManager* pManager)
    : CGameState(pManager), m_pFont(NULL), m_iCurrentSelection(0),
    m_pCurrentGame(NULL)
{
}

void CMenuState::Init()
{
    m_pFont = new GameFont("vector battle", 20);
    m_pFontSmall = new GameFont("vector battle", 15);
    m_pFontLarge = new GameFont("vector battle", 40);
    m_pFontSmall2 = new GameFont("vector battle", 10);

    int dy = int(1.0 / 12.0 * geWorld.scrHeight);
    int left = int(1.0 / 4.0 * geWorld.scrWidth);
    int right = int(3.0 / 4.0 * geWorld.scrWidth);
    int top = int(1.0 / 4.5 * geWorld.scrHeight);
    int bottom = top + dy;

    m_pTitleText = new TextControl(m_pFontLarge, ui::Rectanglei(0, top, 0, geWorld.scrWidth));
    m_pTitleText->setAlignement(TextControl::taCenter);
    m_pTitleText->setText("Asteroids 2010");

    m_pNewGameText = new TextControl(m_pFont, ui::Rectanglei(top, bottom, left, right));
    m_pNewGameText->setAlignement(TextControl::taCenter);
    m_pNewGameText->setText("New game");

    top += dy; bottom += dy;
    m_pResumeGameText = new TextControl(m_pFont, ui::Rectanglei(top, bottom, left, right));
    m_pResumeGameText->setAlignement(TextControl::taCenter);
    m_pResumeGameText->setText("Resume game");

    top += dy; bottom += dy;
    m_pOptionsText = new TextControl(m_pFont, ui::Rectanglei(top, bottom, left, right));
    m_pOptionsText->setAlignement(TextControl::taCenter);
    m_pOptionsText->setText("Settings");

    top += dy; bottom += dy;
    m_pScoresText = new TextControl(m_pFont, ui::Rectanglei(top, bottom, left, right));
    m_pScoresText->setAlignement(TextControl::taCenter);
    m_pScoresText->setText("High scores");

    top += dy; bottom += dy;
    m_pExitText = new TextControl(m_pFont, ui::Rectanglei(top, bottom, left, right));
    m_pExitText->setAlignement(TextControl::taCenter);
    m_pExitText->setText("Exit");
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
        m_pResumeGameText->setTextColor(0.3f, 0.3f, 0.3f);
    }
    else {
        m_pResumeGameText->setTextColor(1.0f, 1.0f, 1.0f);
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
    TextControl* pTxtCtrl = GetTextControl(m_iCurrentSelection);
    if (pTxtCtrl) pTxtCtrl->update(TimeStep);
}

void CMenuState::Draw()
{
    //auto dm = ast::DrawMode2DText();
    glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
    glLoadIdentity();			 // Reset The Projection Matrix
    glOrtho(0, geWorld.scrWidth, geWorld.scrHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);	 // Select The Modelview Matrix
    glLoadIdentity();			 // Reset The Modelview Matrix
    
    m_pTitleText->draw();
    m_pNewGameText->draw();
    m_pResumeGameText->draw();
    m_pOptionsText->draw();
    m_pScoresText->draw();
    m_pExitText->draw();

    TextControl txtControls(m_pFontSmall2, ui::Rectanglei(int(0.7 * geWorld.scrHeight), int(0.7 * geWorld.scrHeight + 20), 0, geWorld.scrWidth));
    txtControls.setAlignement(TextControl::taCenter);
    txtControls.setTextColor(0.8f, 0.8f, 0.8f);
    txtControls.setText("Controls:");
    txtControls.draw();
    txtControls.rect.offsetRect(0, 20);
    txtControls.setText("left arrow - turn left, right arrow - turn right");
    txtControls.draw();
    txtControls.rect.offsetRect(0, 20);
    txtControls.setText("up arrow - forward, space - fire");
    txtControls.draw();

    TextControl line(m_pFontSmall, ui::Rectanglei(geWorld.scrHeight - 100, geWorld.scrHeight - 50, 0, geWorld.scrWidth));
    line.setAlignement(TextControl::taCenter);
    line.setTextColor(0.7f, 0.7f, 0.7f);
    line.setText("Asteroids remake by Piotr Slomski");
    line.draw();
}

TextControl* CMenuState::GetTextControl(int id)
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
    TextControl* pTxtCtrl = GetTextControl(m_iCurrentSelection);
    if (pTxtCtrl) pTxtCtrl->setBlink(in_bBlink);
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
} // namespace ui
