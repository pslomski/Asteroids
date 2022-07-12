#pragma once

#include "ui/Font.hpp"
#include "ui/TextControl.h"
#include "ui/gstate/GameState.h"

namespace ui
{
class OptionsState : public GameState
{
public:
    static OptionsState* getInstance(StateManager* const manager);
    void onKeyDown(SDL_KeyboardEvent& e) override;
    void update(double TimeStep) override;
    void draw() override;
    void enterState() override;
    void leaveState() override;

protected:
    OptionsState(StateManager* const manager);

private:
    static constexpr int MusicVolume{0};
    static constexpr int SoundVolume{1};
    
    void init();
    void cleanup();
    void selectionUp();
    void selectionDown();
    void leftArrow();
    void rightArrow();
    TextControl* getTextControl(int id);
    void setBlinkText(int id, bool isBlink);

    int currentSelection;
    Font* font;
    TextControl* titleText;
    TextControl* musicVolText;
    TextControl* soundVolText;
};
} // namespace ui
