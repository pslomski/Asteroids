#pragma once

#include <SDL.h>
#include "Asteroid.h"
#include "GameConsts.h"
#include "Object.h"
#include "ObjectSound.h"
#include "ScoreCounter.hpp"
#include "Ship.hpp"
#include "Sound.h"
#include "Types.h"
#include "Ufo.h"

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
    void clearBackground();
    void generateBackground();
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
    GLuint m_ListBkg1;
    GLuint m_ListBkg2;

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
