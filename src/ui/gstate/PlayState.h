#pragma once

#include "engine/AsterGame.h"

#include "ui/Font.h"
#include "ui/TextControl.h"

#include "GameState.h"

namespace ui
{
class PlayState : public GameState
{
public:
    static PlayState* getInstance(StateManager* const manager);

    void onKeyDown(SDL_KeyboardEvent& e) override;
    void onKeyUp(SDL_KeyboardEvent& e) override;
    void onResize(int cx, int cy) override;
    void update(double timeStep) override;
    void draw() override;
    void enterState() override;
    void leaveState() override;

    bool isGameOver();
    void reset();

protected:
    PlayState(StateManager* const manager);

private:
    ge::AsterGame asterGame;
    ui::Font* fontSmall;
    ui::Font* fontLarge;
    TextControl* gameOverText;
    bool isDispFps;

    void init();
    void cleanup();
};
} // namespace ui
