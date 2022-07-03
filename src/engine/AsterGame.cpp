#include <assert.h>
#include <time.h>
#include <process.h>

#include "AsterGame.h"
#include "GameConsts.h"
#include "Sound.h"
#include "World.h"

namespace ge
{
AsterGame::AsterGame():
    score(this),
    m_FrameCount(0),
    FPS(0.0)
{
    sndBroom.Init(SND_BROOM, SND_VOL_BROOM);
    sndStartBeep.Init(SND_START_BEEP, SND_VOL_START_BEEP);
    sndBonusBeep.Init(SND_BONUS_BEEP, SND_VOL_BONUS_BEEP);
    sndPowerUp.Init(SND_POWERUP, SND_VOL_POWERUP);
    tiChangeBroomSoundFreq.interval = GE_TI_CHANGE_BROOM_FREQ;
    tiFPS.interval = 1.0;
    ship = NULL;
    ufo = NULL;
    gameState = gsRun;
    gameLevel = 1;
    Lives = GE_INITIAL_LIVES;
    m_AstersCount = GE_INITIAL_ASTER_COUNT;
    m_ListBkg1 = 0;
    m_ListBkg2 = 0;
    tiPause.reset(GE_PAUSE_TIME);
    tiGameStart.reset(1.2);
    tiUfoRespawn.interval = GE_BASE_UFO_TIME;
    m_BeepCount = 0;
    m_pitch = 0.5;
    m_gain = 0.5;
}

AsterGame::~AsterGame()
{
}

void AsterGame::generateBackground(void)
{
    int w = int(geWorld.getWidth());
    int h = int(geWorld.GetHeight());
    Float col;

    if (!m_ListBkg1)
    {
        m_ListBkg1 = glGenLists(1);
        glNewList(m_ListBkg1, GL_COMPILE);
        col = 0.4 + RAND(21) / 20;
        glColor3d(col, col, col);
        glBegin(GL_POINTS);
        for (int i = 0; i < 50; ++i)
        {
            glVertex2d(rand() % w, rand() % h);
        }
        glEnd();
        glEndList();
    }
    if (!m_ListBkg2)
    {
        m_ListBkg2 = glGenLists(1);
        glNewList(m_ListBkg2, GL_COMPILE);
        glBegin(GL_POINTS);
        col = 0.6 + RAND(21) / 20;
        glColor3d(col, col, col);
        for (int i = 0; i < 50; ++i)
        {
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

void AsterGame::Update(void)
{
    Object::dt = geWorld.dt;
    ++m_FrameCount;
    if (tiFPS.inc(Object::dt))
    {
        FPS = m_FrameCount / tiFPS.elapsed;
        tiFPS.reset();
        m_FrameCount = 0;
    }
    ProcessUserInput();
    analyzeGameState();
    CheckCollisions();
    UpdateObjects();
}

void AsterGame::Clear(void)
{
    geSound.Stop();
    for (int i = 0; i < 256; ++i) Key[i] = false;
    for (int i = 0; i < 256; ++i) Keypress[i] = false;

    ClearBackground();

    if (ship) delete ship;
    ship = NULL;

    if (ufo) delete ufo;
    ufo = NULL;

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
        int iAngle = std::min(170, 110 + 10 * iGameLevel);
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
    gameState = gsStartGame;
    gameLevel = 1;
    score.reset();
    Lives = GE_INITIAL_LIVES;
    tiPause.reset(GE_PAUSE_TIME);

    PointF pt = geWorld.GetCenter();
    ship = new PlayerShip(pt.x, pt.y, 90.0);
    generateBackground();
    geSound.Unmute();
    geMusic.Stop();
    tiBroomSound.reset(5.0);
    bPitchBroomSound = false;
    tiChangeBroomSoundFreq.reset(GE_TI_CHANGE_BROOM_FREQ);
    tiUfoRespawn.reset(GE_BASE_UFO_TIME + rand() % 4);
    for (int i = 0; i < 20; ++i) vecStarBlink.push_back(new TStarBlink());
    return true;
};

void AsterGame::ProcessUserInput(void)
{
    if (Key[SDL_SCANCODE_UP]) {
        if (ship) ship->AccelerationOn();
    }
    if (!Key[SDL_SCANCODE_UP]) {
        if (ship) ship->AccelerationOff();
    }
    if (Key[SDL_SCANCODE_LEFT]) {
        if (ship) ship->RotateLeft();
    }
    else {
        if (ship) ship->RotateLeftStop();
    }
    if (Key[SDL_SCANCODE_RIGHT]) {
        if (ship) ship->RotateRight();
    }
    else {
        if (ship) ship->RotateRightStop();
    }
    if (Key[SDL_SCANCODE_SPACE] && !Keypress[SDL_SCANCODE_SPACE]) {
        Keypress[SDL_SCANCODE_SPACE] = true;
        if (ship) {
            if (vecBullets.size() < ship->MaxBullets) {
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

void threadStartMusic(void* p)
{
    Sleep(1000);
    geMusic.Play(TRUE);
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
            if (m_BeepCount > 2)
            {
                pitch = m_pitch * 2.0f;
                gain = m_gain * 1.5f;
                gameState = gsRun;
                GenerateAsters(m_AstersCount, gameLevel);
                _beginthread(threadStartMusic, 0, NULL);
            }
            else
            {
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

        if (NULL == ship) {
            // Ship destroyed
            --Lives;
            if (Lives > 0) {
                gameState = gsShipDestroyed;
                tiPause.reset(GE_PAUSE_TIME);
            }
            else {
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
                if (tiUfoRespawn.inc(Object::dt)) {
                    tiUfoRespawn.reset(std::max(15.0, tiUfoRespawn.interval - 1));
                    ufo = new TUfo;
                    ufo->SetXY(geWorld.GetRandomPosAtEdge());
                }
            }
        }
    }
    break;
    case gsNextLevelPause:
        if (tiPause.inc(Object::dt)) {
            tiPause.reset();
            gameState = gsRun;
            if (vecAsters.empty()) {
                ++m_AstersCount;
                m_AstersCount = std::min(m_AstersCount, GE_MAX_ASTER_COUNT);
                GenerateAsters(m_AstersCount, gameLevel++);
                tiBroomSound.reset();
                tiBroomSound.reset(5.0);
                tiChangeBroomSoundFreq.interval += 2;
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
            geSound.Stop();//SetSoundVol(ALfloat(1.0-tiPause.Ratio()));
        break;
    }
}

void AsterGame::UpdateObjects()
{
    if (ship) {
        if (ship->Respawning) ship->Respawn();
        ship->Update();
    }

    if (ufo) {
        ufo->Update();
        ufo->pAster = NULL;
    }

    Float Rmin = 1e6;
    TvecAsterIt itAster;
    for (itAster = vecAsters.begin(); itAster != vecAsters.end(); itAster++) {
        (*itAster)->update();
        if (ufo) {
            Float Dist = geObDist(ufo, (*itAster));
            if (Dist < Rmin) {
                Rmin = Dist;
                ufo->pAster = (*itAster);
            }
        }
    }

    TvecBulletIt itBullet;
    for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();) {
        if ((*itBullet)->Expired())
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

    for (itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();) {
        if ((*itBullet)->Expired())
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
    for (itOb = vecDebris.begin(); itOb != vecDebris.end();) {
        if ((*itOb)->Expired()) {
            delete (*itOb);
            itOb = vecDebris.erase(itOb);
        }
        else {
            (*itOb)->update();
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

    if (ufo) {
        ufo->pShip = ship;
        ufo->Action(vecUfoBullets);
    }

    for (TvecObiektIt it = vecStarBlink.begin(); it != vecStarBlink.end(); ++it) {
        (*it)->update();
    }
}

void AsterGame::CheckCollisions(void)
{
    TvecAster vecAstersTmp;

    //kolizja Statek-Ufo
    if (ufo) {
        if (ship && !ship->Respawning && ship->CheckCollision(ufo)) {
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
        for (itBullet = vecBullets.begin(); itBullet != vecBullets.end();) {
            if (ufo->CheckCollision(*itBullet)) {
                score.inc(ufo->ScoreValue);
                delete (*itBullet);
                itBullet = vecBullets.erase(itBullet);
                ufo->Crash(vecDebris);
                delete ufo;
                ufo = NULL;
                break;
            }
            else {
                ++itBullet;
            }
        }
    }

    //kolizja Strzal_Ufo-Statek
    if (ship && !ship->Respawning) {
        for (TvecBulletIt itBullet = vecUfoBullets.begin(); itBullet != vecUfoBullets.end();) {
            if (ship->CheckCollision(*itBullet)) {
                delete (*itBullet);
                itBullet = vecUfoBullets.erase(itBullet);
                ship->Crash(vecDebris);
                delete ship;
                ship = NULL;
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
        if (ship && !ship->Respawning && ship->CheckCollision(*itAster)) {
            ship->Crash(vecDebris);
            delete ship;
            ship = NULL;

            (*itAster)->Crash(vecAstersTmp, vecDebris, vecBonus);
            delete (*itAster);
            itAster = vecAsters.erase(itAster);
            bIncrement = false;
            if (itAster == vecAsters.end())
                break;
        };//if (Ship->CheckCollision(*itAster)){

        if (ufo && ufo->CheckCollision(*itAster))
        {
            ufo->Crash(vecDebris);
            delete ufo;
            ufo = NULL;
            tiUfoRespawn.reset();

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
                score.inc((*itAster)->ScoreValue);
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
    if (ship) {
        for (TvecBonusIt it = vecBonus.begin(); it != vecBonus.end();) {
            if (ship->CheckCollision(*it)) {
                score.inc((*it)->ScoreValue);
                if ((*it)->Type == btPoints) {
                    sndBonusBeep.Play();
                }
                else {
                    ship->AddBonus((*it)->Type);
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPointSize(1);
    glCallList(m_ListBkg1);
    glPointSize(2);
    glCallList(m_ListBkg2);

    if (ship)
        ship->Draw();

    if (ufo)
        ufo->Draw();

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
