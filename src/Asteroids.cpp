#include <exception>
#include "Exception.h"
#include "engine/World.h"
#include "log/Log.hpp"
#include "sdl/Application.hpp"
#include "sdl/SDLTools.h"
#include "ui/gstate/MenuState.h"

int main(int argc, char* argv[])
{
    using App = sdl::Application;
    using Window = sdl::Window;

    int res = 0;
    try
    {
        App app;
        geWorld.scrHeight = std::min(geWorld.scrHeight, int(0.80 * SDLTools::getScreenSize().height));
        geWorld.scrWidth = geWorld.scrHeight;
        ui::StateManager stateManager;
        stateManager.changeState(ui::MenuState::getInstance(&stateManager));
        Window* window = Window::create(&stateManager, geWorld.scrWidth, geWorld.scrHeight);
        if (window == nullptr)
        {
            throw std::runtime_error("Main window could not be created");
        }
        app.init(window);
        app.run();
    }
    catch(std::exception & e)
    {
        LOG_ERR(e.what());
        res = -1;
    }
    catch(...)
    {
        LOG_ERR("unknown exception");
        res = -1;
    }
    return res;
}
