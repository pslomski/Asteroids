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

    int gameLevel;
    ScoreCounter score;
    int Lives;
    bool IsMusic;
    Float FPS;

    bool Key[256]; // Array Used For The Keyboard Routine
    bool Keypress[256]; // Array Used For The Keyboard Routine

    void Clear();
    bool Reset();
    void Update();
    void Draw();
    bool isGameOver() const;
    void EnterState();
    void LeaveState();

private:
    void PlayStartBeep(float pitch, float gain);
    void GenerateAsters(int iCount, int iGameLevel);
    void ClearBackground();
    void generateBackground();
    void ProcessUserInput();
    void analyzeGameState();
    void UpdateObjects();
    void CheckCollisions();

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
    unsigned int m_AstersCount; //(4) poczatkowa ilosc asteroidow. wzrasta o 1 z kazdym poziomem do max 6
    GLuint m_ListBkg1;
    GLuint m_ListBkg2;

    TimeInterval tiPause;
    TimeInterval tiGameStart;
    TimeInterval tiUfoRespawn;
    TimeInterval tiFPS;
    int m_FrameCount;
    int m_BeepCount;
    float m_pitch;
    float m_gain;
    TimeInterval tiBroomSound;
    bool bPitchBroomSound;
    TimeInterval tiChangeBroomSoundFreq;
};
} // namespace aster