#pragma once

#include <SDL.h>

class SDLTools
{
public:
    struct SDL_Size
    {
        int width;
        int height;
    };

    static SDL_Keycode GetKeycode(SDL_KeyboardEvent& e) { return e.keysym.sym; }
    static SDL_Keycode GetScancode(SDL_KeyboardEvent& e) { return e.keysym.scancode; }
    static SDL_KeyboardEvent* GetKbEvent(SDL_Event* e) { return reinterpret_cast<SDL_KeyboardEvent*>(e); }
    static SDL_TextInputEvent* GetTextInputEvent(SDL_Event* e) { return reinterpret_cast<SDL_TextInputEvent*>(e); }
    static SDL_Size getScreenSize()
    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        SDL_Size size;
        size.width = DM.w;
        size.height = DM.h;
        return size;
    }
};
