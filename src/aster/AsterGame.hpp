#pragma once

#include <SDL.h>

#include "Asteroid.h"
#include "Background.hpp"
#include "GameConsts.h"
#include "Object.h"
#include "ScoreCounter.hpp"
#include "Ship.hpp"
#include "Types.h"
#include "Ufo.h"
#include "sound/ObjectSound.hpp"
#include "sound/Sound.hpp"

namespace aster
{
class AsterGame
{
public:
    AsterGame();
    ~AsterGame();

    void reset();
    void clear();
    void update();
    void draw();
    bool isGameOver() const;
    void EnterState();
    void LeaveState();

    int gameLevel;
    ScoreCounter score;
    int Lives;
    bool IsMusic;
    Float FPS;
    bool Key[256]; // Array Used For The Keyboard Routine
    bool Keypress[256]; // Array Used For The Keyboard Routine

private:
    void generateAsters(const int count, const int gameLevel);
    void playStartBeep(const float pitch, const float gain);
    void processUserInput();
    void analyzeGameState();
    void updateObjects();
    void checkCollisions();

    TGEObjectSound sndBroom;
    TGEObjectSound sndStartBeep;
    TGEObjectSound sndBonusBeep;
    TGEObjectSound sndPowerUp;
    TvecAster vecAsters; // asteroids objects
    TvecBullet vecBullets; // our ship shots
    TvecBullet vecUfoBullets; // enemy ufo shots
    TvecObiekt vecDebris; // particles of destroyed objects
    TvecBonus vecBonus; // bonuses from destroyed asteroids
    TvecObiekt vecStarBlink;
    PlayerShip* ship;
    TUfo* ufo;
    GameState gameState;
    unsigned int astersCount;
    Background background;

    TimeInterval tiPause;
    TimeInterval tiGameStart;
    TimeInterval tiUfoRespawn;
    TimeInterval tiFPS;
    int frameCount;
    int beepCount;
    float initialPitch;
    float initialGain;
    TimeInterval tiBroomSound;
    bool bPitchBroomSound;
    TimeInterval tiChangeBroomSoundFreq;
};
} // namespace aster
