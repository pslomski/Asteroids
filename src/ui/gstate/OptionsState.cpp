#include <assert.h>

#include "MenuState.h"
#include "OptionsState.h"

#include "aster/World.h"
#include "gl/Renderer.hpp"

namespace ui
{
OptionsState::OptionsState(StateManager* const manager) : GameState(manager) {}

OptionsState* OptionsState::getInstance(StateManager* const manager)
{
    static OptionsState instance(manager);
    return &instance;
}

void OptionsState::init()
{
    using Rect = Rectangle;
    currentSelection = 0;
    font = new Font("vector battle", 20);

    int dy = 20;
    int left = int(1.0 / 4.0 * geWorld.scrWidth);
    int right = int(3.0 / 4.0 * geWorld.scrWidth);
    int bottom = 50;
    int top = bottom + dy;
    titleText = new TextControl(font, Rect(left, top, right, bottom));
    titleText->setAlignement(TextControl::taCenter);
    titleText->setText("Settings");

    dy = 45;
    bottom = 135;
    top = bottom + dy;
    musicVolText = new TextControl(font, Rect(left, top, right, bottom));
    musicVolText->setAlignement(TextControl::taCenter);
    musicVolText->setText("Music volume: ");

    bottom += dy;
    top += dy;
    soundVolText = new TextControl(font, Rect(left, top, right, bottom));
    soundVolText->setAlignement(TextControl::taCenter);
    soundVolText->setText("Sound volume: ");
}

void OptionsState::cleanup()
{
    delete font;
    delete titleText;
    delete musicVolText;
    delete soundVolText;
}

void OptionsState::enterState()
{
    init();
    geWorld.readSettings();
    setBlinkText(currentSelection, true);
}

void OptionsState::leaveState()
{
    geWorld.saveSettings();
    cleanup();
}

void OptionsState::onKeyDown(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_DOWN:
            selectionDown();
            break;
        case SDLK_UP:
            selectionUp();
            break;
        case SDLK_LEFT:
            leftArrow();
            break;
        case SDLK_RIGHT:
            rightArrow();
            break;
        case SDLK_ESCAPE:
            changeState(MenuState::getInstance(stateManager));
            break;
    }
}

void OptionsState::update(double TimeStep)
{
    TextControl* txtCtrl = getTextControl(currentSelection);
    if (txtCtrl) txtCtrl->update(TimeStep);
}

void OptionsState::draw()
{
    auto dm = gl::DrawMode2DText(geWorld.scrWidth, geWorld.scrHeight);
    static const int BUF_SIZE = 128;
    static char buf[BUF_SIZE];
    titleText->draw();

    int musicVol = int(ceil(10 * sound::geMusic.GetVolume()));
    int soundVol = int(ceil(10 * sound::geSound.GetVolume()));
    sprintf(buf, "Music volume: %d", musicVol);
    musicVolText->setText(std::string(buf));
    musicVolText->draw();
    sprintf(buf, "Sound volume: %d", soundVol);
    soundVolText->setText(buf);
    soundVolText->draw();
}

TextControl* OptionsState::getTextControl(int id)
{
    switch (id)
    {
        case 0:
            return musicVolText;
            break;
        case 1:
            return soundVolText;
            break;
    }
    assert(NULL);
    return nullptr;
}

void OptionsState::setBlinkText(int id, bool isBlink)
{
    TextControl* txtCtrl = getTextControl(currentSelection);
    if (txtCtrl) txtCtrl->setBlink(isBlink);
}

void OptionsState::selectionUp()
{
    setBlinkText(currentSelection, false);
    currentSelection--;
    if (currentSelection <= -1)
    {
        currentSelection = 1;
    }
    setBlinkText(currentSelection, true);
}

void OptionsState::selectionDown()
{
    setBlinkText(currentSelection, false);
    currentSelection++;
    if (currentSelection >= 2)
    {
        currentSelection = 0;
    }
    setBlinkText(currentSelection, true);
}

void OptionsState::leftArrow()
{
    switch (currentSelection)
    {
        case MusicVolume:
            geWorld.MusicVol = std::max(0, geWorld.MusicVol - 1);
            sound::geMusic.SetVolume(0.1f * geWorld.MusicVol);
            break;
        case SoundVolume:
            geWorld.SoundVol = std::max(0, geWorld.SoundVol - 1);
            sound::geSound.SetVolume(0.1f * geWorld.SoundVol);
            sound::geSound.SoundTest();
            break;
    }
}

void OptionsState::rightArrow()
{
    switch (currentSelection)
    {
        case MusicVolume:
            geWorld.MusicVol = std::min(10, geWorld.MusicVol + 1);
            sound::geMusic.SetVolume(0.1f * geWorld.MusicVol);
            break;
        case SoundVolume:
            geWorld.SoundVol = std::min(10, geWorld.SoundVol + 1);
            sound::geSound.SetVolume(0.1f * geWorld.SoundVol);
            sound::geSound.SoundTest();
            break;
    }
}
} // namespace ui
