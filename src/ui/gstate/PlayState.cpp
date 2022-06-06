#include "engine/World.h"
#include "engine/Consts.h"
#include "engine/renderer.h"
#include "sdl/SDLTools.h"

#include "HighScoreState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "StateManager.h"

namespace ui
{
#define FNTSIZESMALL 15
#define FNTSIZELARGE 25

PlayState::PlayState(StateManager* pManager)
    : CGameState(pManager), m_pFontSmall(NULL), m_pFontLarge(NULL)
{
}

void PlayState::Init()
{
    m_bDispFPS = false;
    m_pFontSmall = new Font("vector battle", FNTSIZESMALL);
    m_pFontLarge = new Font("vector battle", FNTSIZELARGE);

    m_pGameOverText = new TextControl(m_pFontLarge, ui::Rectangle(0, geWorld.scrHeight, 0, geWorld.scrWidth));
    m_pGameOverText->setAlignement(TextControl::taCenter);
    m_pGameOverText->setText("Game Over");
}

void PlayState::Cleanup()
{
    delete m_pFontSmall;
    delete m_pFontLarge;
    delete m_pGameOverText;
}

PlayState* PlayState::GetInstance(StateManager* pManager)
{
    static PlayState Instance(pManager);
    return &Instance;
}

void PlayState::EnterState()
{
    Init();
    AsterGame.EnterState();
    geWorld.IsGameRunning = true;
    AsterGame.IsMusic = geMusic.GetVolume() > 0.001;
    geSound.Unmute();
    if (geMusic.IsStarted())
        geMusic.Play();
}

void PlayState::LeaveState()
{
    geWorld.IsGameRunning = false;
    AsterGame.LeaveState();
    geSound.Mute();
    if (AsterGame.IsGameOver())
        geMusic.Stop();
    else
        geMusic.Pause();
    Cleanup();
}

void PlayState::Reset()
{
    AsterGame.Reset();
}

void PlayState::OnKeyDown(SDL_KeyboardEvent& e)
{
    AsterGame.Key[SDLTools::GetScancode(e)] = true;
    SDL_Keycode keycode = SDLTools::GetKeycode(e);
    switch (keycode) {
    case SDLK_f: m_bDispFPS = !m_bDispFPS;
    case SDLK_ESCAPE:
    case SDLK_RETURN:
        if (AsterGame.IsGameOver()) {
            HighScoreState* pHighScores = HighScoreState::GetInstance(m_pStateManager);
            pHighScores->SetNewHighScore(AsterGame.Score.Get());
            AsterGame.Clear();
            ChangeState(pHighScores);
        }
        else {
            if (keycode == SDLK_ESCAPE)
                ChangeState(CMenuState::GetInstance(m_pStateManager));
        }
        break;
    }
}

void PlayState::OnKeyUp(SDL_KeyboardEvent& e)
{
    AsterGame.Key[SDLTools::GetScancode(e)] = false;
}

void PlayState::OnResize(int cx, int cy)
{
}

void PlayState::Update(double TimeStep)
{
    AsterGame.Update();
}

void PlayState::Draw()
{
    AsterGame.Draw();

    auto dm = ast::DrawMode2DText();
    GLColor color(1.0, 1.0, 1.0);
    GLint w = GLint(geWorld.scrWidth);
    GLint h = GLint(geWorld.scrHeight);
    GLint y = FNTSIZESMALL + 5;
    m_pFontSmall->drawFmtText(10, y, color, "Level: %d", AsterGame.GameLevel);
    m_pFontSmall->drawFmtText(w / 2 - 80, y, color, "Score: %d", AsterGame.Score.Get());
    m_pFontSmall->drawFmtText(w - 150, y, color, "Lives: %d", AsterGame.Lives);
    if (m_bDispFPS)
        m_pFontSmall->drawFmtText(w / 2 - 80, y + 20, color, "FPS: %.0f", AsterGame.FPS);

    if (IsGameOver())
        m_pGameOverText->draw();
}
} // namespace ui
