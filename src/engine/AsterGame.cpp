#include "stdafx.h"
#include <time.h>
#include <process.h>
#include "AsterGame.h"
#include "Sound.h"
#include "World.h"
#include "GameConsts.h"

namespace ge {

	void ScoreCounter::Inc(int Pts)
	{
		m_Score += Pts;
		if (m_Score >= m_NextLife) {
			m_NextLife += GE_NEXT_LIFE_SCORE;
			pAG->Lives++;
			m_Level++;
		}
	}

	AsterGame::AsterGame() :
		m_FrameCount(0), FPS(0.0)
	{
		sndBroom.Init(SND_BROOM, SND_VOL_BROOM);
		sndStartBeep.Init(SND_START_BEEP, SND_VOL_START_BEEP);
		sndBonusBeep.Init(SND_BONUS_BEEP, SND_VOL_BONUS_BEEP);
		sndPowerUp.Init(SND_POWERUP, SND_VOL_POWERUP);
		tiChangeBroomSoundFreq.interval = GE_TI_CHANGE_BROOM_FREQ;
		Score.pAG = this;
		tiFPS.interval = 1.0;
		Ship = NULL;
		pUfo = NULL;
		m_GameState = gsRun;
		GameLevel = 1;
		Lives = GE_INITIAL_LIVES;
		m_AstersCount = GE_INITIAL_ASTER_COUNT;
		m_ListBkg1 = 0;
		m_ListBkg2 = 0;
		tiPause.Reset(GE_PAUSE_TIME);
		tiGameStart.Reset(1.2);
		tiUfoRespawn.interval = GE_BASE_UFO_TIME;
		m_BeepCount = 0;
		m_pitch = 0.5;
		m_gain = 0.5;
	}

	AsterGame::~AsterGame()
	{
	}

	void AsterGame::GenerateBackground(void)
	{
		int w = int(geWorld.getWidth());
		int h = int(geWorld.GetHeight());
		Float col;

		if (!m_ListBkg1) {
			m_ListBkg1 = glGenLists(1);
			glNewList(m_ListBkg1, GL_COMPILE);
			col = 0.4 + RAND(21) / 20;
			glColor3d(col, col, col);
			glBegin(GL_POINTS);
			for (int i = 0; i < 50; ++i) {
				glVertex2d(rand() % w, rand() % h);
			}
			glEnd();
			glEndList();
		}
		if (!m_ListBkg2) {
			m_ListBkg2 = glGenLists(1);
			glNewList(m_ListBkg2, GL_COMPILE);
			glBegin(GL_POINTS);
			col = 0.6 + RAND(21) / 20;
			glColor3d(col, col, col);
			for (int i = 0; i < 50; ++i) {
				glVertex2d(rand() % w, rand() % h);
			}
			glEnd();
			glEndList();
		}
	}

	void AsterGame::ClearBackground(void)
	{
		if (m_ListBkg1) glDeleteLists(m_ListBkg1, 1);
		m_ListBkg1 = 0;
		if (m_ListBkg2) glDeleteLists(m_ListBkg2, 1);
		m_ListBkg2 = 0;
	}

	void AsterGame::EnterState()
	{
		if (pUfo) {
			pUfo->sndEngine.Play();
		}
		if (Ship) {
			Ship->sndEngine.Stop();
		}
	}

	void AsterGame::LeaveState()
	{
		if (pUfo) {
			pUfo->sndEngine.Pause();
		}
	}

	void AsterGame::Update(void)
	{
		Object::dt = geWorld.dt;
		++m_FrameCount;
		if (tiFPS.Inc(Object::dt)) {
			FPS = m_FrameCount / tiFPS.elapsed;
			tiFPS.Reset();
			m_FrameCount = 0;
		}
		ProcessUserInput();
		AnalyzeGameState();
		CheckCollisions();
		UpdateObjects();
	}

	void AsterGame::Clear(void)
	{
		geSound.Stop();
		for (int i = 0; i < 256; ++i) Key[i] = false;
		for (int i = 0; i < 256; ++i) Keypress[i] = false;

		ClearBackground();

		if (Ship) delete Ship;
		Ship = NULL;

		if (pUfo) delete pUfo;
		pUfo = NULL;

		TvecBulletIt bullet;
		for (bullet = vecBullets.begin(); bullet != vecBullets.end(); bullet++) {
			delete (*bullet);
		}
		vecBullets.clear();

		for (bullet = vecUfoBullets.begin(); bullet != vecUfoBullets.end(); bullet++) {
			delete (*bullet);
		}
		vecUfoBullets.clear();

		TvecAsterIt itAster;
		for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++) {
			delete (*itAster);
		}
		vecAsters.clear();

		TvecObiektIt itOb;
		for (itOb = vecDebris.begin(); itOb != vecDebris.end(); itOb++) {
			delete (*itOb);
		}
		vecDebris.clear();

		TvecBonusIt itB;
		for (itB = vecBonus.begin(); itB != vecBonus.end(); itB++) delete (*itB);
		vecBonus.clear();

		for (itOb = vecStarBlink.begin(); itOb != vecStarBlink.end(); itOb++) {
			delete (*itOb);
		}
		vecStarBlink.clear();
	};

	void AsterGame::GenerateAsters(int iCount, int iGameLevel)
	{
		for (int i = 0; i < iCount; ++i) {
			Asteroid* pAster = new Asteroid(1);
			//if(i<4) pAster->HasBonus=true;
			int iSide = i % 4;
			int iPart = rand() % 4;
			int iAngle = min(170, 110 + 10 * iGameLevel);
			iAngle = rand() % iAngle - iAngle / 2;
			if (0 == iSide) {
				pAster->SetXY(geWorld.clipLeft, iPart / 4.0 * (geWorld.clipTop + geWorld.clipBottom));
				pAster->SetAlfa(iAngle);
			}
			else if (1 == iSide) {
				pAster->SetXY(geWorld.clipRight, iPart / 4.0 * (geWorld.clipTop + geWorld.clipBottom));
				pAster->SetAlfa(iAngle + 180.0);
			}
			else if (2 == iSide) {
				pAster->SetXY(iPart / 4.0 * (geWorld.clipLeft + geWorld.clipRight), geWorld.clipBottom);
				pAster->SetAlfa(iAngle + 90);
			}
			else if (3 == iSide) {
				pAster->SetXY(iPart / 4.0 * (geWorld.clipLeft + geWorld.clipRight), geWorld.clipTop);
				pAster->SetAlfa(iAngle - 90);
			}
			pAster->SetV(3.0 + rand() % 5 + iGameLevel * 0.25);
			vecAsters.push_back(pAster);
		}
	};

	void AsterGame::PlayStartBeep(float pitch, float gain)
	{
		sndStartBeep.SetVolume(gain);
		sndStartBeep.SetPitch(pitch);
		sndStartBeep.Play();
	}

	bool AsterGame::Reset(void)
	{
		Clear();
		srand((unsigned)time(NULL));
		m_AstersCount = GE_INITIAL_ASTER_COUNT;//(4) poczatkowa liczba asteroidow. wzrasta o 1 z kazdym poziomem do max 6
		m_BeepCount = 0;
		m_GameState = gsStartGame;
		GameLevel = 1;
		Score.Reset();
		Lives = GE_INITIAL_LIVES;
		tiPause.Reset(GE_PAUSE_TIME);

		PointF pt = geWorld.GetCenter();
		Ship = new PlayerShip(pt.x, pt.y, 90.0);
		GenerateBackground();
		geSound.Unmute();
		geMusic.Stop();
		tiBroomSound.Reset(5.0);
		bPitchBroomSound = false;
		tiChangeBroomSoundFreq.Reset(GE_TI_CHANGE_BROOM_FREQ);
		tiUfoRespawn.Reset(GE_BASE_UFO_TIME + rand() % 4);
		for (int i = 0; i < 20; ++i) vecStarBlink.push_back(new TStarBlink());
		return true;
	};

	void AsterGame::ProcessUserInput(void)
	{
		if (Key[SDL_SCANCODE_UP]) {
			if (Ship) Ship->AccelerationOn();
		}
		if (!Key[SDL_SCANCODE_UP]) {
			if (Ship) Ship->AccelerationOff();
		}
		if (Key[SDL_SCANCODE_LEFT]) {
			if (Ship) Ship->RotateLeft();
		}
		else {
			if (Ship) Ship->RotateLeftStop();
		}
		if (Key[SDL_SCANCODE_RIGHT]) {
			if (Ship) Ship->RotateRight();
		}
		else {
			if (Ship) Ship->RotateRightStop();
		}
		if (Key[SDL_SCANCODE_SPACE] && !Keypress[SDL_SCANCODE_SPACE]) {
			Keypress[SDL_SCANCODE_SPACE] = true;
			if (Ship) {
				if (vecBullets.size() < Ship->MaxBullets) {
					TBullet* pB = Ship->FireBullet();
					if (pB) vecBullets.push_back(pB);
				}
			}
		}
		if (!Key[SDL_SCANCODE_SPACE])
		{
			Keypress[SDL_SCANCODE_SPACE] = false;
		}
	}

	void threadStartMusic(void* p)
	{
		Sleep(1000);
		geMusic.Play(TRUE);
	}

	void AsterGame::AnalyzeGameState(void)
	{
		switch (m_GameState) {
		case gsStartGame:
		{
			if (tiGameStart.Inc(Object::dt)) {
				tiGameStart.Reset();
				float pitch, gain;
				if (m_BeepCount > 2) {
					pitch = m_pitch * 2.0f;
					gain = m_gain * 1.5f;
					m_GameState = gsRun;
					GenerateAsters(m_AstersCount, GameLevel);
					_beginthread(threadStartMusic, 0, NULL);
				}
				else {
					pitch = m_pitch;
					gain = m_gain;
				}
				PlayStartBeep(pitch, gain);
				++m_BeepCount;
			}
		}
		break;
		case gsRun:
		{
			if (tiChangeBroomSoundFreq.Inc(Object::dt)) {
				tiChangeBroomSoundFreq.Reset();
				tiBroomSound.interval -= 1;
				tiBroomSound.interval = max(tiBroomSound.interval, 0.7);
			}

			if (tiBroomSound.Inc(Object::dt)) {
				tiBroomSound.Reset();
				if (bPitchBroomSound) {
					sndBroom.SetPitch(1.05f);
				}
				else {
					sndBroom.SetPitch(1.0f);
				}
				if (!IsMusic) sndBroom.Play();
				bPitchBroomSound = !bPitchBroomSound;
			}

			if (NULL == Ship) {
				// Ship destroyed
				--Lives;
				if (Lives > 0) {
					m_GameState = gsShipDestroyed;
					tiPause.Reset(GE_PAUSE_TIME);
				}
				else {
					m_GameState = gsGameOver;
					tiPause.Reset(GE_GAMEOVER_PAUSE_TIME);
				}
			}
			else if (vecAsters.empty() && !pUfo) {
				// Level up
				m_GameState = gsNextLevelPause;
				tiPause.Reset(GE_PAUSE_TIME);
				tiUfoRespawn.Reset(GE_BASE_UFO_TIME + rand() % 4 - 2);
			}
			else {
				if (!pUfo) {
					// Handle Ufo
					if (tiUfoRespawn.Inc(Object::dt)) {
						tiUfoRespawn.Reset(max(15.0, tiUfoRespawn.interval - 1));
						pUfo = new TUfo;
						pUfo->SetXY(geWorld.GetRandomPosAtEdge());
					}
				}
			}
		}
		break;
		case gsNextLevelPause:
			if (tiPause.Inc(Object::dt)) {
				tiPause.Reset();
				m_GameState = gsRun;
				if (vecAsters.empty()) {
					++m_AstersCount;
					m_AstersCount = min(m_AstersCount, GE_MAX_ASTER_COUNT);
					GenerateAsters(m_AstersCount, GameLevel++);
					tiBroomSound.Reset();
					tiBroomSound.interval = 5.0;
					tiChangeBroomSoundFreq.interval += 2;
				}
			}
			break;
		case gsShipDestroyed:
			if (tiPause.Inc(Object::dt)) {
				tiPause.Reset();
				assert(NULL == Ship);
				if (NULL == Ship) {
					m_GameState = gsRun;
					PointF pt = geWorld.GetCenter();
					Ship = new PlayerShip(pt.x, pt.y, 90.0);
					Ship->Respawning = true;
				}
			}
			break;
		case gsGameOver:
			if (tiPause.Inc(Object::dt))
				geSound.Stop();//SetSoundVol(ALfloat(1.0-tiPause.Ratio()));
			break;
		}
	}

	void AsterGame::UpdateObjects(void)
	{
		if (Ship) {
			if (Ship->Respawning) Ship->Respawn();
			Ship->Update();
		}

		if (pUfo) {
			pUfo->Update();
			pUfo->pAster = NULL;
		}

		Float Rmin = 1e6;
		TvecAsterIt itAster;
		for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++) {
			(*itAster)->Update();
			if (pUfo) {
				Float Dist = geObDist(pUfo, (*itAster));
				if (Dist < Rmin) {
					Rmin = Dist;
					pUfo->pAster = (*itAster);
				}
			}
		}

		TvecBulletIt itBullet;
		for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();) {
			if ((*itBullet)->Expired()) {
				delete (*itBullet);
				itBullet = vecBullets.erase(itBullet);
			}
			else {
				(*itBullet)->Update();
				++itBullet;
			}
		}

		for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();) {
			if ((*itBullet)->Expired()) {
				delete (*itBullet);
				itBullet = vecUfoBullets.erase(itBullet);
			}
			else {
				(*itBullet)->Update();
				++itBullet;
			}
		}

		TvecObiektIt itOb;
		for (itOb = vecDebris.begin(); itOb != vecDebris.end();) {
			if ((*itOb)->Expired()) {
				delete (*itOb);
				itOb = vecDebris.erase(itOb);
			}
			else {
				(*itOb)->Update();
				++itOb;
			}
		}

		for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end();) {
			if ((*it)->Expired()) {
				delete (*it);
				it = vecBonus.erase(it);
			}
			else {
				(*it)->Update();
				++it;
			}
		}

		if (pUfo) {
			pUfo->pShip = Ship;
			pUfo->Action(vecUfoBullets);
		}

		for (TvecObiektIt it = vecStarBlink.begin(); it != vecStarBlink.end(); ++it) {
			(*it)->Update();
		}
	}

	void AsterGame::CheckCollisions(void)
	{
		TvecAster vecAstersTmp;

		//kolizja Statek-Ufo
		if (pUfo) {
			if (Ship && !Ship->Respawning && Ship->CheckCollision(pUfo)) {
				Ship->Crash(vecDebris);
				delete Ship;
				Ship = NULL;
				pUfo->Crash(vecDebris);
				delete pUfo;
				pUfo = NULL;
				tiUfoRespawn.Reset();
			}
		}

		//kolizja Strzal_nasz-Ufo
		if (pUfo) {
			TvecBulletIt itBullet;
			for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();) {
				if (pUfo->CheckCollision(*itBullet)) {
					Score.Inc(pUfo->ScoreValue);
					delete (*itBullet);
					itBullet = vecBullets.erase(itBullet);
					pUfo->Crash(vecDebris);
					delete pUfo;
					pUfo = NULL;
					break;
				}
				else {
					++itBullet;
				}
			}
		}

		//kolizja Strzal_Ufo-Statek
		if (Ship && !Ship->Respawning) {
			for (TvecBulletIt itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();) {
				if (Ship->CheckCollision(*itBullet)) {
					delete (*itBullet);
					itBullet = vecUfoBullets.erase(itBullet);
					Ship->Crash(vecDebris);
					delete Ship;
					Ship = NULL;
					break;
				}
				else {
					++itBullet;
				}
			}
		}

		//tutaj sprawdzanie kolizji z asteroidami i ew. strzalami przeciwnika
		TvecAsterIt itAster;
		for (itAster = vecAsters.begin(); itAster != vecAsters.end();) {

			bool bIncrement = true;
			if (Ship && !Ship->Respawning && Ship->CheckCollision(*itAster)) {
				Ship->Crash(vecDebris);
				delete Ship;
				Ship = NULL;

				(*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
				delete (*itAster);
				itAster = vecAsters.erase(itAster);
				bIncrement = false;
				if (itAster == vecAsters.end())
					break;
			};//if (Ship->CheckCollision(*itAster)){

			if (pUfo && pUfo->CheckCollision(*itAster)) {
				pUfo->Crash(vecDebris);
				delete pUfo;
				pUfo = NULL;
				tiUfoRespawn.Reset();

				Asteroid::CreateBonus = false;//ufo nie generuje bonusow
				(*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
				Asteroid::CreateBonus = true;
				delete (*itAster);
				itAster = vecAsters.erase(itAster);
				bIncrement = false;
				if (itAster == vecAsters.end())
					break;
			};//if (pUfo->CheckCollision(*itAster)){

			TvecBulletIt itBullet;
			for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();) {
				if ((*itAster)->CheckCollision(*itBullet)) {
					delete (*itBullet);
					itBullet = vecBullets.erase(itBullet);
					Score.Inc((*itAster)->ScoreValue);
					(*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
					delete (*itAster);
					itAster = vecAsters.erase(itAster);
					bIncrement = false;
					if (itAster == vecAsters.end())
						break;
				}
				else {
					++itBullet;
				}
			}

			if (itAster != vecAsters.end()) {
				for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();) {
					if ((*itAster)->CheckCollision(*itBullet)) {
						delete (*itBullet);
						itBullet = vecUfoBullets.erase(itBullet);

						Asteroid::CreateBonus = false;//ufo nie generuje bonusow
						(*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
						Asteroid::CreateBonus = true;
						delete (*itAster);
						itAster = vecAsters.erase(itAster);
						bIncrement = false;
						if (itAster == vecAsters.end())
							break;
					}
					else {
						++itBullet;
					}
				}
			}
			if (bIncrement)
				++itAster;
		}//for(itAster=vecAsters.begin(); itAster!=vecAsters.end(); itAster++){

		for (itAster = vecAstersTmp.begin(); itAster != vecAstersTmp.end(); itAster++) {
			vecAsters.push_back(*itAster);
		}

		//kolizja Statek-Bonus
		if (Ship) {
			for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end();) {
				if (Ship->CheckCollision(*it)) {
					Score.Inc((*it)->ScoreValue);
					if ((*it)->Type == btPoints) {
						sndBonusBeep.Play();
					}
					else {
						Ship->AddBonus((*it)->Type);
						sndPowerUp.Play();
					}
					delete (*it);
					it = vecBonus.erase(it);
					break;
				}
				else {
					++it;
				}
			}
		}
	}

	void AsterGame::Draw(void)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, geWorld.getWidth(), 0, geWorld.GetHeight(), -1, 1);

		//glMatrixMode(GL_MODELVIEW);	 // Select The Modelview Matrix
		//glLoadIdentity();			 // Reset The Modelview Matrix

		glPointSize(1);
		glCallList(m_ListBkg1);
		glPointSize(2);
		glCallList(m_ListBkg2);

		if (Ship)
			Ship->Draw();

		if (pUfo)
			pUfo->Draw();

		TvecAsterIt itAster;
		for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++) {
			(*itAster)->Draw();
		}

		TvecBulletIt itBullet;
		for (itBullet = vecBullets.begin(); itBullet != vecBullets.end(); ++itBullet) {
			(*itBullet)->Draw();
		}

		for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end(); ++itBullet) {
			(*itBullet)->Draw();
		}

		for (TvecObiektIt itOb = vecDebris.begin(); itOb != vecDebris.end(); ++itOb) {
			(*itOb)->Draw();
		}

		for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end(); ++it) {
			(*it)->Draw();
		}

		for (TvecObiektIt it = vecStarBlink.begin(); it != vecStarBlink.end(); ++it) {
			(*it)->Draw();
		}
	}

} // namespace ge