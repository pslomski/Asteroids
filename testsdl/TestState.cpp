#include <assert.h>
#include "TestState.hpp"

#include "gl/Renderer.h"
#include "log/Log.hpp"
#include "sdl/SDLApplication.h"
#include "sdl/SDLTools.h"
#include "ui/gstate/StateManager.h"

namespace ui
{
TestState::TestState(StateManager* pManager) :
    GameState(pManager)
{
}

void TestState::Init()
{
    font = new Font("vector battle", 20);
    titleText = new TextControl(font, Rectangle(0, 100, 600, 300));
    titleText->setAlignement(TextControl::taCenter);
    titleText->setText("Asteroids 2010");
}

void TestState::Cleanup()
{
    delete font;
    delete titleText;
    font = nullptr;
    titleText = nullptr;
}

void TestState::EnterState()
{
    Init();
}

void TestState::LeaveState()
{
    Cleanup();
}

void TestState::OnKeyDown(SDL_KeyboardEvent& e)
{
    switch (SDLTools::GetKeycode(e))
    {
    case SDLK_ESCAPE:
        ExitGame();
        break;
    }
}

void TestState::Update(double TimeStep)
{
}

void TestState::Draw()
{
    int width{600};
    int height{600};
    glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
    glLoadIdentity();            // Reset The Projection Matrix
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);  // Select The Modelview Matrix
    glLoadIdentity();            // Reset The Modelview Matrix
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(0, 600);
    glVertex2d(600, 0);
    glEnd();

    gl::Renderer::enter2DMode(width, height);
    titleText->draw();
    gl::Renderer::leave2DMode();
}

void TestState::ExitGame()
{
    SDLApplication::quitApp();
}
} // namespace ui
