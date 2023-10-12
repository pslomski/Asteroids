#include <assert.h>

#include "HighScoreState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "PlayState.h"
#include "StateManager.h"

#include "aster/Consts.h"
#include "aster/World.h"
#include "gl/Renderer.hpp"
#include "log/Log.hpp"
#include "sdl/Application.hpp"
#include "sdl/SDLTools.h"

namespace ui
{
using Application = sdl::Application;

MenuState::MenuState(StateManager* const manager)
    : GameState(manager), font(nullptr), currentSelection(0), currentGame(nullptr)
{
}

void MenuState::init()
{
    font = new Font("vector battle", 20);
    fontSmall = new Font("vector battle", 15);
    fontSmall2 = new Font("vector battle", 10);
    fontLarge = new Font("vector battle", 40);

    int dy = int(1.0 / 12.0 * geWorld.scrHeight);
    int left = int(1.0 / 4.0 * geWorld.scrWidth);
    int right = int(3.0 / 4.0 * geWorld.scrWidth);
    int bottom = int(1.0 / 4.5 * geWorld.scrHeight);
    int top = bottom + dy;

    titleText = new TextControl(fontLarge, Rectangle(left, top, right, bottom));
    titleText->setAlignement(TextControl::taCenter);
    titleText->setText("Asteroids 2010");

    newGameText = new TextControl(font, Rectangle(left, top, right, bottom));
    newGameText->setAlignement(TextControl::taCenter);
    newGameText->setText("New game");

    top += dy;
    bottom += dy;
    resumeGameText = new TextControl(font, Rectangle(left, top, right, bottom));
    resumeGameText->setAlignement(TextControl::taCenter);
    resumeGameText->setText("Resume game");

    top += dy;
    bottom += dy;
    optionsText = new TextControl(font, Rectangle(left, top, right, bottom));
    optionsText->setAlignement(TextControl::taCenter);
    optionsText->setText("Settings");

    top += dy;
    bottom += dy;
    scoresText = new TextControl(font, Rectangle(left, top, right, bottom));
    scoresText->setAlignement(TextControl::taCenter);
    scoresText->setText("High scores");

    top += dy;
    bottom += dy;
    exitText = new TextControl(font, Rectangle(left, top, right, bottom));
    exitText->setAlignement(TextControl::taCenter);
    exitText->setText("Exit");
}

void MenuState::cleanup()
{
    delete font;
    delete fontSmall;
    delete fontSmall2;
    delete fontLarge;
    delete titleText;
    delete newGameText;
    delete resumeGameText;
    delete scoresText;
    delete exitText;
    delete optionsText;

    font = nullptr;
    fontSmall = nullptr;
    fontSmall2 = nullptr;
    fontLarge = nullptr;
    titleText = nullptr;
    newGameText = nullptr;
    resumeGameText = nullptr;
    scoresText = nullptr;
    exitText = nullptr;
    optionsText = nullptr;
}

void MenuState::enterState()
{
    LOG_INF("MenuState::enterState");
    init();
    setBlinkText(currentSelection, false);
    if (!currentGame or currentGame->isGameOver())
    {
        if (1 == currentSelection)
        {
            currentSelection = 0;
        }
        resumeGameText->setTextColor(0.3f, 0.3f, 0.3f);
    }
    else
    {
        resumeGameText->setTextColor(1.0f, 1.0f, 1.0f);
    }
    setBlinkText(currentSelection, true);
}

void MenuState::leaveState()
{
    cleanup();
    LOG_INF("MenuState::leaveState");
}

MenuState* MenuState::getInstance(StateManager* const manager)
{
    static MenuState instance(manager);
    return &instance;
}

void MenuState::onKeyDown(SDL_KeyboardEvent& e)
{
    switch (SDLTools::GetKeycode(e))
    {
        case SDLK_DOWN:
            selectionDown();
            break;
        case SDLK_UP:
            selectionUp();
            break;
        case SDLK_RETURN:
            selectionChosen();
            break;
        case SDLK_ESCAPE:
            exitGame();
            break;
    }
}

void MenuState::update(double TimeStep)
{
    TextControl* pTxtCtrl = getTextControl(currentSelection);
    if (pTxtCtrl) pTxtCtrl->update(TimeStep);
}

void MenuState::draw()
{
    gl::Renderer::enter2DMode(geWorld.scrWidth, geWorld.scrHeight);
    titleText->draw();
    newGameText->draw();
    resumeGameText->draw();
    optionsText->draw();
    scoresText->draw();
    exitText->draw();

    TextControl txtControls(
        fontSmall2, Rectangle(0, int(0.7 * geWorld.scrHeight + 20), geWorld.scrWidth, int(0.7 * geWorld.scrHeight)));
    txtControls.setAlignement(TextControl::taCenter);
    txtControls.setTextColor(0.8f, 0.8f, 0.8f);
    txtControls.setText("Controls:");
    txtControls.draw();
    txtControls.rect.offset(0, 20);
    txtControls.setText("left arrow - turn left, right arrow - turn right");
    txtControls.draw();
    txtControls.rect.offset(0, 20);
    txtControls.setText("up arrow - forward, space - fire");
    txtControls.draw();

    TextControl line(fontSmall, Rectangle(0, geWorld.scrHeight - 50, geWorld.scrWidth, geWorld.scrHeight - 100));
    line.setAlignement(TextControl::taCenter);
    line.setTextColor(0.7f, 0.7f, 0.7f);
    line.setText("Asteroids remake");
    line.draw();
    gl::Renderer::leave2DMode();
}

TextControl* MenuState::getTextControl(const int id)
{
    switch (id)
    {
        case 0:
            return newGameText;
        case 1:
            return resumeGameText;
        case 2:
            return optionsText;
        case 3:
            return scoresText;
        case 4:
            return exitText;
    }
    assert(false);
    return nullptr;
}

void MenuState::setBlinkText(const int id, const bool isBlink)
{
    TextControl* textCtrl = getTextControl(currentSelection);
    if (textCtrl)
    {
        textCtrl->setBlink(isBlink);
    }
}

void MenuState::selectionUp()
{
    setBlinkText(currentSelection, false);
    currentSelection--;
    if (currentSelection == -1)
    {
        currentSelection = 4;
    }

    // If there is no current game, we should skip
    // the "Resume game" item.
    if (currentSelection == 1)
    {
        if (!currentGame or currentGame->isGameOver())
        {
            currentSelection--;
        }
    }
    setBlinkText(currentSelection, true);
}

void MenuState::selectionDown()
{
    setBlinkText(currentSelection, false);
    currentSelection++;
    if (currentSelection == 5)
    {
        currentSelection = 0;
    }

    // If there is no current game, we should skip
    // the "Resume game" item.
    if (currentSelection == 1)
    {
        if (!currentGame or currentGame->isGameOver())
        {
            currentSelection++;
        }
    }
    setBlinkText(currentSelection, true);
}

void MenuState::selectionChosen()
{
    switch (currentSelection)
    {
        case 0:
            if (!currentGame)
            {
                currentGame = PlayState::getInstance(stateManager);
            }
            currentGame->reset();
            setBlinkText(currentSelection, false);
            currentSelection = 1;
            setBlinkText(currentSelection, true);
            changeState(currentGame);
            break;
        case 1:
            if (currentGame and !currentGame->isGameOver())
            {
                changeState(currentGame);
            }
            break;
        case 2:
            changeState(OptionsState::getInstance(stateManager));
            break;
        case 3:
            changeState(HighScoreState::getInstance(stateManager));
            break;
        case 4:
            Application::quitApp();
            break;
    }
}

void MenuState::exitGame()
{
    Application::quitApp();
}
} // namespace ui
