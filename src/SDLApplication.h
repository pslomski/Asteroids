#pragma once

#ifndef _SDL_APPLICATION_H_
#define _SDL_APPLICATION_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "SDLWindow.h"

class SDLApplication
{
private:
	static bool fQuit;
	SDLWindow *fPtrWnd;
	void OnEvent(SDL_Event* e);
public:
	static void QuitApp() { fQuit = true; }
	void Init();
	void Run();
	void Cleanup();
};

#endif  // _SDL_APPLICATION_H_