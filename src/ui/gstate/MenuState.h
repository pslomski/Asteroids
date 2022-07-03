#pragma once

#include "GameState.h"
#include "PlayState.h"

#include "ui/Font.h"
#include "ui/TextControl.h"

namespace ui
{
class MenuState : public GameState
{
public:
    static MenuState* getInstance(StateManager* const manager);
    void onKeyDown(SDL_KeyboardEvent&) override;
    void update(double TimeStep) override;
    void draw() override;
    void enterState() override;
    void leaveState() override;

protected:
    MenuState(StateManager* const manager);

private:
    void init();
    void cleanup();
    void selectionUp();
    void selectionDown();
    void selectionChosen();
    void exitGame();
    TextControl* getTextControl(const int id);
    void setBlinkText(const int id, const bool isBlink);

    Font* font;
    Font* fontSmall;
    Font* fontSmall2;
    Font* fontLarge;
    int currentSelection;
    PlayState* currentGame;
    TextControl* titleText;
    TextControl* newGameText;
    TextControl* resumeGameText;
    TextControl* scoresText;
    TextControl* exitText;
    TextControl* optionsText;
};
} // namespace ui
