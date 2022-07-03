#define SDL_MAIN_HANDLED
#include <assert.h>
#include <SDL_ttf.h>

class App
{ 
public:
    App()
    {
        setUp();
    }

    ~App()
    {
        tearDown();
    }

    void setUp()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw "SDL library initialization failed";
        }
        if(TTF_Init() == -1)
        {
            throw "Could not initialize SDL2_ttf";
        }
        font = TTF_OpenFont("vectorb.ttf", 32);
    }

    void tearDown()
    {
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }

    TTF_Font* font{nullptr};
};

int main(int argc, char* argv[])
{
    App app;
    
    SDL_Window* window = SDL_CreateWindow("C++ SDL2 Window", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
    assert(window != nullptr);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != nullptr);

    // Pixels from our text
    SDL_Surface* surf = TTF_RenderText_Solid(app.font, "0123456789", {255, 255, 255});
    assert(surf != nullptr);

    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surf);
    assert(textureText != nullptr);

    // Free the surface
    // We are done with it after we have uploaded to the texture
    SDL_FreeSurface(surf);

    // Create a rectangle to draw on
    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 400;
    rectangle.h = 100;

    int res;
    // Clear and Draw the Screen
    // Gives us a clear "canvas"
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render our text on a rectangle
    SDL_RenderCopy(renderer, textureText, NULL, &rectangle);

    // Finally show what we've drawn
    SDL_RenderPresent(renderer);

    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }

        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render our text on a rectangle
        SDL_RenderCopy(renderer,textureText,NULL,&rectangle);

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }
    // Destroy our textured text
    SDL_DestroyTexture(textureText);
    SDL_DestroyWindow(window);
    return 0;
}
