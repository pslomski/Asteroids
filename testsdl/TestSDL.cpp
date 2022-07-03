#include <exception>
#include "Exception.h"
#include "engine/World.h"
#include "log/Log.hpp"
#include "sdl/SDLApplication.h"
#include "sdl/SDLTools.h"

#include "TestState.hpp"

int main(int argc, char* argv[])
{
    LOG_INF("TestSDL::main argv[0]:%s", argv[0]);
    int res = 0;
    try
    {
        SDLApplication app;

        geWorld.scrHeight = std::min(geWorld.scrHeight, int(0.80 * SDLTools::getScreenSize().height));
        geWorld.scrWidth = geWorld.scrHeight;

        ui::StateManager stateManager;
        ui::TestState testState(&stateManager);
        stateManager.changeState(&testState);
        SDLWindow* window = SDLWindow::create(&stateManager, geWorld.scrWidth, geWorld.scrHeight);
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
