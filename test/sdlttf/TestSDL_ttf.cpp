#include <gtest/gtest.h>
#include <SDL_ttf.h>

namespace testing
{
class SDL_ttfTest: public Test
{ 
public: 
   void SetUp( )
   {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw "SDL library initialization failed";
        }
        if(TTF_Init() == -1)
        {
            throw "Could not initialize SDL2_ttf";
        }
   }

   void TearDown( )
   {
       TTF_CloseFont(font);
       TTF_Quit();
       SDL_Quit();
   }
protected:
    TTF_Font* font{nullptr};
};

TEST_F(SDL_ttfTest, testTTF_OpenFont)
{
    font = TTF_OpenFont("vectorb.ttf", 32);
    ASSERT_TRUE(font != nullptr);
}

TEST_F(SDL_ttfTest, DISABLED_shouldRenderFont)
{
    font = TTF_OpenFont("vectorb.ttf", 32);
    ASSERT_TRUE(font != nullptr);

    SDL_Window* window = SDL_CreateWindow("C++ SDL2 Window", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
    ASSERT_TRUE(window != nullptr);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ASSERT_TRUE(renderer != nullptr);

    // Pixels from our text
    SDL_Surface* surf = TTF_RenderText_Solid(font, "0123456789", {255, 255, 255});
    ASSERT_TRUE(surf != nullptr);

    // Setup the texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surf);
    ASSERT_TRUE(textureText != nullptr);

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
    ASSERT_EQ(0, SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE));
    ASSERT_EQ(0, SDL_RenderClear(renderer));

    // Render our text on a rectangle
    ASSERT_EQ(0, SDL_RenderCopy(renderer, textureText, NULL, &rectangle));

    // Destroy our textured text
    SDL_DestroyTexture(textureText);
    SDL_DestroyWindow(window);
}
}
