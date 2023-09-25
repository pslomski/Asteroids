#include "AsterGame.hpp"

#include <assert.h>
#include <time.h>

#include "GameConsts.h"
#include "StarBlink.hpp"
#include "World.h"
#include "sound/Sound.hpp"

namespace aster
{
AsterGame::AsterGame():
    score(this),
    frameCount(0),
    FPS(0.0)
{
    sndBroom.Init(SND_BROOM, SND_VOL_BROOM);
    sndStartBeep.Init(SND_START_BEEP, SND_VOL_START_BEEP);
    sndBonusBeep.Init(SND_BONUS_BEEP, SND_VOL_BONUS_BEEP);
    sndPowerUp.Init(SND_POWERUP, SND_VOL_POWERUP);
    tiChangeBroomSoundFreq.set(GE_TI_CHANGE_BROOM_FREQ);
    tiFPS.set(1.0);
    ship = NULL;
    ufo = NULL;
    gameState = gsRun;
    gameLevel = 1;
    Lives = GE_INITIAL_LIVES;
    astersCount = GE_INITIAL_ASTER_COUNT;
    tiPause.reset(GE_PAUSE_TIME);
    tiGameStart.reset(1.2);
    tiUfoRespawn.set(GE_BASE_UFO_TIME);
    beepCount = 0;
    initialPitch = 0.5;
    initialGain = 0.5;
}

AsterGame::~AsterGame()
{
}

void AsterGame::reset()
{
    clear();
    srand((unsigned)time(NULL));
    astersCount = GE_INITIAL_ASTER_COUNT;
    beepCount = 0;
    gameState = gsStartGame;
    gameLevel = 1;
    score.reset();
    Lives = GE_INITIAL_LIVES;
    tiPause.reset(GE_PAUSE_TIME);

    PointF pt = geWorld.GetCenter();
    ship = new PlayerShip(pt.x, pt.y, 90.0);
    background.generate();
    sound::geSound.Unmute();
    sound::geMusic.Stop();
    tiBroomSound.reset(5.0);
    bPitchBroomSound = false;
    tiChangeBroomSoundFreq.reset(GE_TI_CHANGE_BROOM_FREQ);
    tiUfoRespawn.reset(GE_BASE_UFO_TIME + rand() % 4);
    for (int i = 0; i < 20; ++i)
    {
        vecStarBlink.push_back(new TStarBlink());
    }
}

void AsterGame::clear()
{
    sound::geSound.Stop();
    for (int i = 0; i < 256; ++i)
    {
        Key[i] = false;
    }
    for (int i = 0; i < 256; ++i)
    {
        Keypress[i] = false;
    }
    background.clear();
    if (ship)
    {
        delete ship;
    }
    ship = NULL;

    if (ufo)
    {
        delete ufo;
    }
    ufo = NULL;

    TvecBulletIt bullet;
    for (bullet = vecBullets.begin(); bullet != vecBullets.end(); bullet++)
    {
        delete (*bullet);
    }
    vecBullets.clear();

    for (bullet = vecUfoBullets.begin(); bullet != vecUfoBullets.end(); bullet++)
    {
        delete (*bullet);
    }
    vecUfoBullets.clear();

    TvecAsterIt itAster;
    for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++)
    {
        delete (*itAster);
    }
    vecAsters.clear();

    TvecObiektIt itOb;
    for (itOb = vecDebris.begin(); itOb != vecDebris.end(); itOb++)
    {
        delete (*itOb);
    }
    vecDebris.clear();

    TvecBonusIt itB;
    for (itB = vecBonus.begin(); itB != vecBonus.end(); itB++)
    {
        delete (*itB);
    }
    vecBonus.clear();

    for (itOb = vecStarBlink.begin(); itOb != vecStarBlink.end(); itOb++)
    {
        delete (*itOb);
    }
    vecStarBlink.clear();
};

void AsterGame::generateAsters(const int count, const int gameLevel)
{
    for (int i = 0; i < count; ++i)
    {
        Asteroid* pAster = new Asteroid(1);
        int iSide = i % 4;
        int iPart = rand() % 4;
        int iAngle = std::min(170, 110 + 10 * gameLevel);
        iAngle = rand() % iAngle - iAngle / 2;
        if (0 == iSide) 
        {
            pAster->SetXY(geWorld.clipLeft, iPart / 4.0 * (geWorld.clipTop + geWorld.clipBottom));
            pAster->SetAlfa(iAngle);
        }
        else if (1 == iSide)
        {
            pAster->SetXY(geWorld.clipRight, iPart / 4.0 * (geWorld.clipTop + geWorld.clipBottom));
            pAster->SetAlfa(iAngle + 180.0);
        }
        else if (2 == iSide)
        {
            pAster->SetXY(iPart / 4.0 * (geWorld.clipLeft + geWorld.clipRight), geWorld.clipBottom);
            pAster->SetAlfa(iAngle + 90);
        }
        else if (3 == iSide)
        {
            pAster->SetXY(iPart / 4.0 * (geWorld.clipLeft + geWorld.clipRight), geWorld.clipTop);
            pAster->SetAlfa(iAngle - 90);
        }
        pAster->SetV(3.0 + rand() % 5 + gameLevel * 0.25);
        vecAsters.push_back(pAster);
    }
};

bool  AsterGame::isGameOver() const
{
    return gsGameOver == gameState;
}

void AsterGame::EnterState()
{
    if (ufo) {
        ufo->sndEngine.Play();
    }
    if (ship) {
        ship->sndEngine.Stop();
    }
}

void AsterGame::LeaveState()
{
    if (ufo) {
        ufo->sndEngine.Pause();
    }
}

void AsterGame::update()
{
    Object::dt = geWorld.dt;
    ++frameCount;
    if (tiFPS.inc(Object::dt))
    {
        FPS = frameCount / tiFPS.elapsed;
        tiFPS.reset();
        frameCount = 0;
    }
    processUserInput();
    analyzeGameState();
    checkCollisions();
    updateObjects();
}

void AsterGame::playStartBeep(const float pitch, const float gain)
{
    sndStartBeep.SetVolume(gain);
    sndStartBeep.SetPitch(pitch);
    sndStartBeep.Play();
}

void AsterGame::processUserInput()
{
    if (Key[SDL_SCANCODE_UP])
    {
        if (ship) ship->AccelerationOn();
    }
    if (!Key[SDL_SCANCODE_UP])
    {
        if (ship) ship->AccelerationOff();
    }
    if (Key[SDL_SCANCODE_LEFT])
    {
        if (ship) ship->RotateLeft();
    }
    else
    {
        if (ship) ship->RotateLeftStop();
    }
    if (Key[SDL_SCANCODE_RIGHT])
    {
        if (ship) ship->RotateRight();
    }
    else
    {
        if (ship) ship->RotateRightStop();
    }
    if (Key[SDL_SCANCODE_SPACE] && !Keypress[SDL_SCANCODE_SPACE])
    {
        Keypress[SDL_SCANCODE_SPACE] = true;
        if (ship)
        {
            if (vecBullets.size() < ship->MaxBullets)
            {
                TBullet* pB = ship->FireBullet();
                if (pB) vecBullets.push_back(pB);
            }
        }
    }
    if (!Key[SDL_SCANCODE_SPACE])
    {
        Keypress[SDL_SCANCODE_SPACE] = false;
    }
}

int threadStartMusic(void* p)
{
    SDL_Delay(1000);
    sound::geMusic.Play(TRUE);
    return 0;
}

void AsterGame::analyzeGameState()
{
    switch (gameState)
    {
    case gsStartGame:
    {
        if (tiGameStart.inc(Object::dt))
        {
            tiGameStart.reset();
            float pitch, gain;
            if (beepCount > 2)
            {
                pitch = initialPitch * 2.0f;
                gain = initialGain * 1.5f;
                gameState = gsRun;
                generateAsters(astersCount, gameLevel);
                SDL_CreateThread(threadStartMusic, "threadMusic", nullptr);
            }
            else
            {
                pitch = initialPitch;
                gain = initialGain;
            }
            playStartBeep(pitch, gain);
            ++beepCount;
        }
    }
    break;
    case gsRun:
    {
        if (tiChangeBroomSoundFreq.inc(Object::dt))
        {
            tiChangeBroomSoundFreq.reset();
            tiBroomSound.interval -= 1;
            tiBroomSound.interval = std::max(tiBroomSound.interval, 0.7);
        }

        if (tiBroomSound.inc(Object::dt))
        {
            tiBroomSound.reset();
            if (bPitchBroomSound)
            {
                sndBroom.SetPitch(1.05f);
            }
            else
            {
                sndBroom.SetPitch(1.0f);
            }
            if (not IsMusic)
            {
                sndBroom.Play();
            }
            bPitchBroomSound = not bPitchBroomSound;
        }

        if (NULL == ship)
        {
            // Ship destroyed
            --Lives;
            if (Lives > 0)
            {
                gameState = gsShipDestroyed;
                tiPause.reset(GE_PAUSE_TIME);
            }
            else
            {
                gameState = gsGameOver;
                tiPause.reset(GE_GAMEOVER_PAUSE_TIME);
            }
        }
        else if (vecAsters.empty() && !ufo)
        {
            // Level up
            gameState = gsNextLevelPause;
            tiPause.reset(GE_PAUSE_TIME);
            tiUfoRespawn.reset(GE_BASE_UFO_TIME + RAND(4) - 2);
        }
        else
        {
            if (!ufo) 
            {
                // Handle Ufo
                if (tiUfoRespawn.inc(Object::dt))
                {
                    tiUfoRespawn.reset(std::max(15.0, tiUfoRespawn.interval - 1));
                    ufo = new TUfo;
                    ufo->SetXY(geWorld.GetRandomPosAtEdge());
                }
            }
        }
    }
    break;
    case gsNextLevelPause:
        if (tiPause.inc(Object::dt))
        {
            tiPause.reset();
            gameState = gsRun;
            if (vecAsters.empty())
            {
                ++astersCount;
                astersCount = std::min(astersCount, GE_MAX_ASTER_COUNT);
                generateAsters(astersCount, gameLevel++);
                tiBroomSound.reset(5.0);
                tiChangeBroomSoundFreq.inc(2.0);
            }
        }
        break;
    case gsShipDestroyed:
        if (tiPause.inc(Object::dt))
        {
            tiPause.reset();
            assert(nullptr == ship);
            if (nullptr == ship)
            {
                gameState = gsRun;
                PointF pt = geWorld.GetCenter();
                ship = new PlayerShip(pt.x, pt.y, 90.0);
                ship->Respawning = true;
            }
        }
        break;
    case gsGameOver:
        if (tiPause.inc(Object::dt))
            sound::geSound.Stop();
        break;
    }
}

void AsterGame::updateObjects()
{
    if (ship)
    {
        if (ship->Respawning) ship->Respawn();
        ship->update();
    }

    if (ufo)
    {
        ufo->update();
        ufo->pAster = nullptr;
    }

    Float rMin = 1e6;
    TvecAsterIt itAster;
    for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++)
    {
        (*itAster)->update();
        if (ufo)
        {
            Float distance = ufo->distance(*itAster);
            if (distance < rMin)
            {
                rMin = distance;
                ufo->pAster = (*itAster);
            }
        }
    }

    TvecBulletIt itBullet;
    for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();)
    {
        if ((*itBullet)->expired())
        {
            delete (*itBullet);
            itBullet = vecBullets.erase(itBullet);
        }
        else
        {
            (*itBullet)->update();
            ++itBullet;
        }
    }

    for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();)
    {
        if ((*itBullet)->expired())
        {
            delete (*itBullet);
            itBullet = vecUfoBullets.erase(itBullet);
        }
        else
        {
            (*itBullet)->update();
            ++itBullet;
        }
    }

    TvecObiektIt itOb;
    for (itOb = vecDebris.begin(); itOb != vecDebris.end();)
    {
        if ((*itOb)->expired())
        {
            delete (*itOb);
            itOb = vecDebris.erase(itOb);
        }
        else
        {
            (*itOb)->update();
            ++itOb;
        }
    }

    for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end();)
    {
        if ((*it)->expired())
        {
            delete (*it);
            it = vecBonus.erase(it);
        }
        else
        {
            (*it)->update();
            ++it;
        }
    }

    if (ufo)
    {
        ufo->pShip = ship;
        ufo->Action(vecUfoBullets);
    }

    for (TvecObiektIt it = vecStarBlink.begin(); it != vecStarBlink.end(); ++it)
    {
        (*it)->update();
    }
}

void AsterGame::checkCollisions()
{
    TvecAster vecAstersTmp;

    //kolizja Statek-Ufo
    if (ufo)
    {
        if (ship && !ship->Respawning && ship->CheckCollision(ufo))
        {
            ship->Crash(vecDebris);
            delete ship;
            ship = NULL;
            ufo->Crash(vecDebris);
            delete ufo;
            ufo = NULL;
            tiUfoRespawn.reset();
        }
    }

    //kolizja Strzal_nasz-Ufo
    if (ufo) {
        TvecBulletIt itBullet;
        for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();)
        {
            if (ufo->CheckCollision(*itBullet))
            {
                score.inc(ufo->ScoreValue);
                delete (*itBullet);
                itBullet = vecBullets.erase(itBullet);
                ufo->Crash(vecDebris);
                delete ufo;
                ufo = NULL;
                break;
            }
            else
            {
                ++itBullet;
            }
        }
    }

    //kolizja Strzal_Ufo-Statek
    if (ship && !ship->Respawning)
    {
        for (TvecBulletIt itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();)
        {
            if (ship->CheckCollision(*itBullet))
            {
                delete (*itBullet);
                itBullet = vecUfoBullets.erase(itBullet);
                ship->Crash(vecDebris);
                delete ship;
                ship = NULL;
                break;
            }
            else
            {
                ++itBullet;
            }
        }
    }

    //tutaj sprawdzanie kolizji z asteroidami i ew. strzalami przeciwnika
    TvecAsterIt itAster;
    for (itAster = vecAsters.begin(); itAster != vecAsters.end();)
    {
        bool bIncrement = true;
        if (ship && !ship->Respawning && ship->CheckCollision(*itAster))
        {
            ship->Crash(vecDebris);
            delete ship;
            ship = nullptr;

            (*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
            delete (*itAster);
            itAster = vecAsters.erase(itAster);
            bIncrement = false;
            if (itAster == vecAsters.end())
            {
                break;
            }
        }

        if (ufo && ufo->CheckCollision(*itAster))
        {
            ufo->Crash(vecDebris);
            delete ufo;
            ufo = NULL;
            tiUfoRespawn.reset();

            Asteroid::CreateBonus = false; // ufo doesn't generate bonuses
            (*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
            Asteroid::CreateBonus = true;
            delete (*itAster);
            itAster = vecAsters.erase(itAster);
            bIncrement = false;
            if (itAster == vecAsters.end())
            {
                break;
            }
        }

        TvecBulletIt itBullet;
        for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();)
        {
            if ((*itAster)->CheckCollision(*itBullet))
            {
                delete (*itBullet);
                itBullet = vecBullets.erase(itBullet);
                score.inc((*itAster)->ScoreValue);
                (*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
                delete (*itAster);
                itAster = vecAsters.erase(itAster);
                bIncrement = false;
                if (itAster == vecAsters.end())
                    break;
            }
            else
            {
                ++itBullet;
            }
        }

        if (itAster != vecAsters.end())
        {
            for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();)
            {
                if ((*itAster)->CheckCollision(*itBullet))
                {
                    delete (*itBullet);
                    itBullet = vecUfoBullets.erase(itBullet);
                    Asteroid::CreateBonus = false; // ufo doesn't generate bonuses
                    (*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
                    Asteroid::CreateBonus = true;
                    delete (*itAster);
                    itAster = vecAsters.erase(itAster);
                    bIncrement = false;
                    if (itAster == vecAsters.end())
                    {
                        break;
                    }
                }
                else
                {
                    ++itBullet;
                }
            }
        }
        if (bIncrement)
        {
            ++itAster;
        }
    }

    for (itAster = vecAstersTmp.begin(); itAster != vecAstersTmp.end(); itAster++)
    {
        vecAsters.push_back(*itAster);
    }

    // Ship-Bonus collision
    if (ship)
    {
        for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end();)
        {
            if (ship->CheckCollision(*it))
            {
                score.inc((*it)->ScoreValue);
                if ((*it)->Type == btPoints)
                {
                    sndBonusBeep.Play();
                }
                else
                {
                    ship->AddBonus((*it)->Type);
                    sndPowerUp.Play();
                }
                delete (*it);
                it = vecBonus.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }
}

void AsterGame::draw()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, geWorld.getWidth(), 0, geWorld.getHeight(), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    background.draw();

    if (ship)
    {
        ship->Draw();
    }

    if (ufo)
    {
        ufo->Draw();
    }

    TvecAsterIt itAster;
    for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++)
    {
        (*itAster)->Draw();
    }

    TvecBulletIt itBullet;
    for (itBullet = vecBullets.begin(); itBullet != vecBullets.end(); ++itBullet)
    {
        (*itBullet)->Draw();
    }

    for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end(); ++itBullet)
    {
        (*itBullet)->Draw();
    }

    for (TvecObiektIt itOb = vecDebris.begin(); itOb != vecDebris.end(); ++itOb)
    {
        (*itOb)->Draw();
    }

    for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end(); ++it)
    {
        (*it)->Draw();
    }

    for (TvecObiektIt it = vecStarBlink.begin(); it != vecStarBlink.end(); ++it)
    {
        (*it)->Draw();
    }
}
} // namespace aster
