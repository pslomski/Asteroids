// Asteroids.cpp : Defines the entry point for the application.
//

#include "Log.h"
#include "SDLApplication.h"

int main(int argc, char* argv[])
{
	int res = 0;
	SDLApplication app;
	try {
		app.Init();
		app.Run();
	}
	catch (std::exception & e) {
		Log::Write(e.what());
		res = -1;
	}
	app.Cleanup();
	return res;
}
