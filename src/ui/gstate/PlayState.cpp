
#include "PlayState.h"
#include "HighScoreState.h"
#include "MenuState.h"
#include "StateManager.h"

#include "aster/Consts.h"
#include "aster/World.h"
#include "gl/Renderer.hpp"
#include "log/Log.hpp"
#include "sdl/SDLTools.h"

namespace ui
{
#define FNTSIZESMALL 15
#define FNTSIZELARGE 25

PlayState::PlayState(StateManager* const manager) : GameState(manager), fontSmall(nullptr), fontLarge(nullptr) {}

void PlayState::init()
{
    isDispFps = false;
    fontSmall = new Font("vector battle", FNTSIZESMALL);
    fontLarge = new Font("vector battle", FNTSIZELARGE);

    gameOverText = new TextControl(fontLarge, ui::Rectangle(0, geWorld.scrHeight, geWorld.scrWidth, 0));
    gameOverText->setAlignement(TextControl::taCenter);
    gameOverText->setText("Game Over");
}

void PlayState::cleanup()
{
    delete fontSmall;
    delete fontLarge;
    delete gameOverText;
}

PlayState* PlayState::getInstance(StateManager* manager)
{
    static PlayState Instance(manager);
    return &Instance;
}

void PlayState::enterState()
{
    LOG_INF("PlayState::enterState");
    init();
    asterGame.EnterState();
    geWorld.IsGameRunning = true;
    asterGame.IsMusic = sound::geMusic.GetVolume() > 0.001;
    sound::geSound.Unmute();
    if (sound::geMusic.IsStarted())
    {
        sound::geMusic.Play();
    }
}

void PlayState::leaveState()
{
    geWorld.IsGameRunning = false;
    asterGame.LeaveState();
    sound::geSound.Mute();
    if (asterGame.isGameOver())
        sound::geMusic.Stop();
    else
        sound::geMusic.Pause();
    cleanup();
    LOG_INF("PlayState::leaveState");
}

void PlayState::reset()
{
    asterGame.reset();
}

bool PlayState::isGameOver()
{
    return asterGame.isGameOver();
}

void PlayState::onKeyDown(SDL_KeyboardEvent& e)
{
    asterGame.Key[SDLTools::GetScancode(e)] = true;
    SDL_Keycode keycode = SDLTools::GetKeycode(e);
    switch (keycode)
    {
        case SDLK_f:
            isDispFps = not isDispFps;
        case SDLK_ESCAPE:
        case SDLK_RETURN:
            if (asterGame.isGameOver())
            {
                HighScoreState* pHighScores = HighScoreState::getInstance(stateManager);
                pHighScores->setNewHighScore(asterGame.score.get());
                asterGame.clear();
                changeState(pHighScores);
            }
            else
            {
                if (keycode == SDLK_ESCAPE)
                {
                    changeState(MenuState::getInstance(stateManager));
                }
            }
            break;
    }
}

void PlayState::onKeyUp(SDL_KeyboardEvent& e)
{
    asterGame.Key[SDLTools::GetScancode(e)] = false;
}

void PlayState::onResize(int cx, int cy) {}

void PlayState::update(double timeStep)
{
    asterGame.update();
}

void PlayState::draw()
{
    asterGame.draw();

    const auto dm = gl::DrawMode2DText(geWorld.scrWidth, geWorld.scrHeight);
    GLColor color(1.0, 1.0, 1.0);
    GLint w = GLint(geWorld.scrWidth);
    GLint h = GLint(geWorld.scrHeight);
    GLint y = FNTSIZESMALL + 5;
    fontSmall->drawFmtText(10, y, color, "Level: %d", asterGame.gameLevel);
    fontSmall->drawFmtText(w / 2 - 80, y, color, "Score: %d", asterGame.score.get());
    fontSmall->drawFmtText(w - 150, y, color, "Lives: %d", asterGame.Lives);
    if (isDispFps)
    {
        fontSmall->drawFmtText(w / 2 - 80, y + 20, color, "FPS: %.0f", asterGame.FPS);
    }
    if (isGameOver())
    {
        gameOverText->draw();
    }
}
} // namespace ui
