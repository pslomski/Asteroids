#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////

#define GE_WORLD_WIDTH 80
#define GE_WORLD_HEIGHT 80
#define GE_SCREEN_WIDTH 800
#define GE_SCREEN_HEIGHT 800

#define GE_GAME_DEBUG

#ifdef GE_GAME_DEBUG
#define GE_INITIAL_LIVES 1
#define GE_BASE_UFO_TIME 30.0
#define GE_INITIAL_ASTER_COUNT 4
#define GE_MAX_ASTER_COUNT 10u
#define GE_INITIAL_MAX_BULLETS 3//liczba pociskow na raz
#define GE_BULLETS_INCREMENT 3//zwiekszenie przez PowerUp
#define GE_INITIAL_BULLET_SPEED 30.0//predkosc pocisku
#define GE_BULLET_SPEED_INC 30.0//zwiekszenie przedkosci przez PowerUp
#define GE_BONUS_LIFETIME 15.0//czas zycia bonusu
#define GE_NEXT_LIFE_SCORE 2000//dodatkowe zycie co GE_NEXT_LIFE_SCORE punktow
#define GE_PAUSE_TIME 2.0
#define GE_GAMEOVER_PAUSE_TIME 5.0
#define GE_POWERUP_DURATION_TIME 20.0
#else
#define GE_INITIAL_LIVES 3
#define GE_BASE_UFO_TIME 30.0
#define GE_INITIAL_ASTER_COUNT 4
#define GE_MAX_ASTER_COUNT 10u
#define GE_INITIAL_MAX_BULLETS 3 // liczba pociskow na raz
#define GE_BULLETS_INCREMENT 3 // zwiekszenie przez PowerUp
#define GE_INITIAL_BULLET_SPEED 35.0 // predkosc pocisku
#define GE_BULLET_SPEED_INC 30.0 // zwiekszenie przedkosci przez PowerUp
#define GE_BONUS_LIFETIME 15.0 // czas zycia bonusu
#define GE_NEXT_LIFE_SCORE 2000 // dodatkowe zycie co GE_NEXT_LIFE_SCORE punktow
#define GE_PAUSE_TIME 2.0
#define GE_GAMEOVER_PAUSE_TIME 5.0
#define GE_POWERUP_DURATION_TIME 20.0
#endif

//sound
#define GE_TI_CHANGE_BROOM_FREQ 10.0

//Points values
#define GE_SCRVAL_UFO    100
#define GE_SCRVAL_ASTER1  10
#define GE_SCRVAL_ASTER2  20
#define GE_SCRVAL_ASTER3  30
#define GE_SCRVAL_BONUS   40

//asteroid
#define GE_ASTER1_DEBR_COUNT 80
#define GE_ASTER2_DEBR_COUNT 70
#define GE_ASTER3_DEBR_COUNT 60

//ship
#define GE_SHIP_DOT_DEBR_COUNT 80
#define GE_SHIP_LIN_DEBR_COUNT 50
#define GE_SHIP_ROT_SPEED 270.0
//ufo
#define GE_UFO_DEBR_COUNT 70

//bonus

#define GE_USE_COLORS

#ifdef GE_USE_COLORS
#define GE_COLOR_WHITE 1.0, 1.0, 1.0
#define GE_COLOR_ASTER GE_COLOR_WHITE
#define GE_UFO_COLOR 0.6, 0.9, 0.2
#define GE_SHIP_COLOR 1.0, 1.0, 0.0
#define GE_SHIP_ENGINE_COLOR 0.9, 0.2, 0.0
#define GE_BONUS_BULLET_SPEED_COLOR 0.2, 0.7, 1.0
#define GE_BONUS_ADD_BULLETS_COLOR 0.9, 0.1, 0.1
#define GE_BONUS_POINTS_COLOR 1.0, 0.6, 0.0
#else
#define GE_COLOR_WHITE 1.0, 1.0, 1.0
#define GE_COLOR_ASTER GE_COLOR_WHITE
#define GE_UFO_COLOR GE_COLOR_WHITE
#define GE_SHIP_COLOR GE_COLOR_WHITE
#define GE_SHIP_ENGINE_COLOR GE_COLOR_WHITE
#define GE_BONUS_BULLET_SPEED_COLOR GE_COLOR_WHITE
#define GE_BONUS_ADD_BULLETS_COLOR GE_COLOR_WHITE
#define GE_BONUS_POINTS_COLOR  GE_COLOR_WHITE
#endif