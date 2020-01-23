#ifndef _ASTER_GAME_H_
#define _ASTER_GAME_H_

#include "SDL.h"
#include "Types.h"
#include "GameConsts.h"
#include "Sound.h"
#include "Object.h"
#include "Ship.h"
#include "Ufo.h"
#include "Asteroid.h"
#include "ObjectSound.h"

namespace ge{

class AsterGame;

class ScoreCounter
{
private:
	int m_Score;
	int m_NextLife;
	int m_Level;
public:
	ScoreCounter(void){pAG=NULL; Reset();}
	void Reset(void){m_Score=0; m_NextLife=GE_NEXT_LIFE_SCORE; m_Level=1;}
	int Get(){return m_Score;}
	void Inc(int Pts);
	AsterGame *pAG;
};

class AsterGame
{
private:
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
	PlayerShip* Ship; // our ship
	TUfo* pUfo; // enemy ufo
	GameState m_GameState;
	unsigned int m_AstersCount;//(4) poczatkowa ilosc asteroidow. wzrasta o 1 z kazdym poziomem do max 6
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

	void PlayStartBeep(float pitch, float gain);
	void GenerateAsters(int iCount, int iGameLevel);
	void ClearBackground(void);
	void GenerateBackground(void);
	void ProcessUserInput(void);
	void AnalyzeGameState(void);
	void UpdateObjects(void);
	void CheckCollisions(void);
public:
	AsterGame();
	~AsterGame();

	int GameLevel;
	ScoreCounter Score;
	int Lives;
	bool IsMusic;
	Float FPS;

	bool Key[256];//Array Used For The Keyboard Routine
	bool Keypress[256];//Array Used For The Keyboard Routine

	void Clear(void);
	bool Reset(void);
	void Update(void);
	void Draw(void);
	bool IsGameOver(){return gsGameOver==m_GameState;}
	void EnterState();
	void LeaveState();
};

} // namespace ge
#endif // _ASTER_GAME_H_