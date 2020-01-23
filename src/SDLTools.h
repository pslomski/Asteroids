#ifndef _SDL_TOOLS_H_
#define _SDL_TOOLS_H_

#include "SDL.h"

class SDLTools {
public:
	static SDL_Keycode GetKeycode(SDL_KeyboardEvent& e) {
		return e.keysym.sym;
	}
	static SDL_Keycode GetScancode(SDL_KeyboardEvent& e) {
		return e.keysym.scancode;
	}
	static SDL_KeyboardEvent* GetKbEvent(SDL_Event* e) {
		return reinterpret_cast<SDL_KeyboardEvent*>(e);
	}
	static SDL_TextInputEvent* GetTextInputEvent(SDL_Event* e) {
		return reinterpret_cast<SDL_TextInputEvent*>(e);
	}
};

#endif // _SDL_TOOLS_H_