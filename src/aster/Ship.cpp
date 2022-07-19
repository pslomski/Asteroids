#include "Ship.hpp"
#include "World.h"
#include "Sound.h"
#include "Consts.h"
#include "GameConsts.h"

#include "aster/ShipDebris.hpp"
#include "aster/AsterShard.hpp"

namespace aster
{
PlayerShip::PlayerShip(Float ax, Float ay, Float aangle):
    Object(),
    puAddBullet(*this, GE_POWERUP_DURATION_TIME),
    puBulletSpeed(*this, GE_POWERUP_DURATION_TIME)
{
    sndFire.Init(SND_SHIP_FIRE, SND_VOL_SHIP_FIRE);
    sndFirePow.Init(SND_SHIP_FIRE_POWER, SND_VOL_SHIP_FIRE_POWER);
    sndEngine.Init(SND_SHIP_ENGINE, SND_VOL_SHIP_ENGINE);
    sndCrash.Init(SND_SHIP_CRASH, SND_VOL_SHIP_CRASH);

    m_tiAccel.interval = 0.5;
    m_tiRespawn.interval = 3.0;
    m_tiFade.interval = 0.15;
    m_tiEngineBlink.interval = 0.25;
    m_tiRotateLeft.interval = 0.25;
    m_tiRotateRight.interval = 0.25;
    m_tiRespawnBlink.interval = 0.3;
    m_RespBlinkColRatio = 1.0;

    BulletSpeed = GE_INITIAL_BULLET_SPEED;
    MaxBullets = GE_INITIAL_MAX_BULLETS;
    ObjGeom = ogPolyg;
    color(GE_SHIP_COLOR);
    clEngine.Set(GE_SHIP_ENGINE_COLOR);
    m_RotSpeed = GE_SHIP_ROT_SPEED;
    SetRotSpeed(0.0);
    SetXY(ax, ay);
    SetAlfa(aangle);
    fshield = false;
    bDarken = false;
    faccelerated = false;
    Respawning = false;
    KDec = 0.05;
    Accel = 20.0; // ok. 2g
    AccelBurst = 15.0;
    AccelMax = Accel + AccelBurst; // pomocnicza przy wyswietlaniu plomienia
    sndEngineGain = 0.0;
    EngSndStopped = true;

    Verts.push_back(PointF(2.0, 0.0));
    Verts.push_back(PointF(-1.5, -1.0));
    Verts.push_back(PointF(-1.0, 0.0));
    Verts.push_back(PointF(-1.5, 1.0));
    CalcBounds(Verts);
}

PlayerShip::~PlayerShip()
{
    sndEngine.Stop();
}

void PlayerShip::update()
{
    Object::update();
    if (puAddBullet.duration.inc(dt))
        puAddBullet.stop();
    if (puBulletSpeed.duration.inc(dt))
        puBulletSpeed.stop();

    if (Respawning)
    {
        if (m_tiRespawnBlink.inc(dt))
        {
            m_tiRespawnBlink.reset();
            bDarken = !bDarken;
        }
        Float d = bDarken ? 0.5 : 1.0;
        m_RespBlinkColRatio = 0.5 * (1 + m_tiRespawnBlink.ratio()) * d;
    }
    else
    {
        m_RespBlinkColRatio = 1.0;
    }

    if (faccelerated)
    {
        if (m_tiEngineBlink.inc(dt))
        {
            m_tiEngineBlink.reset();
        }
    }

    if (faccelerated)
    {
        m_BoostLen = GetA() / AccelBurst * 2.0 + 0.25 * sin(m_tiEngineBlink.ratio() * 2 * GE_PI);
    }

    // compute color
    m_clrTmp = clr;
    if (puAddBullet.isActive())
    {
        Float alfa = 2 * GE_PI * puAddBullet.duration.elapsed;
        Float sina = sin(alfa);
        sina *= sina;
        Float cosa = cos(alfa);
        cosa *= cosa;
        Color cl1(GE_BONUS_ADD_BULLETS_COLOR);
        cl1 = cl1 * sina;
        Color cl2(m_clrTmp);
        cl2 = cl2 * cosa;
        m_clrTmp.r = std::min(1.0, cl1.r + cl2.r);
        m_clrTmp.g = std::min(1.0, cl1.g + cl2.g);
        m_clrTmp.b = std::min(1.0, cl1.b + cl2.b);
    }
    if (puBulletSpeed.isActive())
    {
        Float alfa = 2 * GE_PI * puBulletSpeed.duration.elapsed;
        Float sina = sin(alfa);
        sina *= sina;
        Float cosa = cos(alfa);
        cosa *= cosa;
        Color cl1(GE_BONUS_BULLET_SPEED_COLOR);
        cl1 = cl1 * sina;
        Color cl2(m_clrTmp);
        cl2 = cl2 * cosa;
        m_clrTmp.r = std::min(1.0, cl1.r + cl2.r);
        m_clrTmp.g = std::min(1.0, cl1.g + cl2.g);
        m_clrTmp.b = std::min(1.0, cl1.b + cl2.b);
    }
}

void PlayerShip::OnRender(void)
{
    if (faccelerated)
    {
        glColor3d(m_RespBlinkColRatio * clEngine.r, m_RespBlinkColRatio * clEngine.g, m_RespBlinkColRatio * clEngine.b);
        glBegin(GL_LINE_STRIP);
        glVertex2d(-1.5, -1);
        glVertex2d(-m_BoostLen, 0);
        glVertex2d(-1.5, 1);
        glEnd();
    }

    glColor3d(m_RespBlinkColRatio * m_clrTmp.r, m_RespBlinkColRatio * m_clrTmp.g, m_RespBlinkColRatio * m_clrTmp.b);
    glBegin(GL_LINE_LOOP);
    for (TvecPointFIt it = Verts.begin(); it != Verts.end(); ++it)
        glVertex2d((*it).x, (*it).y);
    glEnd();
}

void PlayerShip::AccelerationOn()
{
    if (m_tiAccel.inc(dt))
        m_tiAccel.elapsed = m_tiAccel.interval;
    SetA(Accel + (1.0 - m_tiAccel.ratio()) * AccelBurst);
    sndEngineGain = SND_VOL_SHIP_ENGINE * GetA() / AccelMax;
    sndEngine.SetPitch(float(GetA() / AccelMax));
    if (!faccelerated)
    {
        sndEngine.SetVolume(float(sndEngineGain));
        sndEngine.Play();
        EngSndStopped = false;
    }
    faccelerated = true;
    m_tiFade.reset();
}

void PlayerShip::AccelerationOff()
{
    if (faccelerated)
    {
        sndEngine.SlideVol(0.0f, 100);
    }

    m_tiAccel.reset();
    SetA(0.0);
    faccelerated = false;
}

void PlayerShip::RotateLeft()
{
    m_tiRotateLeft.inc(dt);
    SetAlfa(GetAlfa() + std::min(0.5 * (1.0 + m_tiRotateLeft.ratio()), 1.0) * m_RotSpeed * dt);
}

void PlayerShip::RotateRight()
{
    m_tiRotateRight.inc(dt);
    SetAlfa(GetAlfa() - std::min(0.5 * (1.0 + m_tiRotateRight.ratio()), 1.0) * m_RotSpeed * dt);
}

TBullet *PlayerShip::FireBullet()
{
    if (puAddBullet.isActive() or puBulletSpeed.isActive())
    {
        sndFirePow.Play();
    }
    else
    {
        sndFire.Play();
    }
    TBullet *bullet = new TBullet;
    bullet->SetXY(GetX(), GetY());
    bullet->SetAlfa(GetAlfa());
    Float vx = GetVX() + BulletSpeed * cos(GetAlfa() * GE_PIover180);
    Float vy = GetVY() + BulletSpeed * sin(GetAlfa() * GE_PIover180);
    bullet->SetV(vx, vy);
    bullet->color(clr);
    return bullet;
}

void PlayerShip::Crash(TvecObiekt &vecObiekty)
{
    sndCrash.Play();

    int iDebCount = GE_SHIP_LIN_DEBR_COUNT;
    for (int i = 0; i < iDebCount; ++i)
    {
        aster::AsterShard *pDeb = new aster::AsterShard;
        pDeb->color(clr);
        pDeb->SetAlfa(GetAlfa() + i * 360.0 / iDebCount + rand() % 16 - 8.0);
        pDeb->SetXY(GetX(), GetY());
        Float vRand = 15.0 + rand() % 5;
        Float vx = GetVX() + vRand * cos(pDeb->GetAlfa() * GE_PIover180);
        Float vy = GetVY() + vRand * sin(pDeb->GetAlfa() * GE_PIover180);
        pDeb->SetV(vx, vy);
        vecObiekty.push_back(pDeb);
    }

    iDebCount = GE_SHIP_DOT_DEBR_COUNT;
    for (int i = 0; i < iDebCount; ++i)
    {
        aster::ShipDebris *pDeb = new aster::ShipDebris;
        pDeb->color(clr);
        pDeb->SetAlfa(GetAlfa() + i * 360.0 / iDebCount + rand() % 16 - 8.0);
        pDeb->SetXY(GetX(), GetY());
        Float vRand = 3.0 + rand() % 15;
        Float vx = 0.8 * GetVX() + vRand * cos(pDeb->GetAlfa() * GE_PIover180);
        Float vy = 0.8 * GetVY() + vRand * sin(pDeb->GetAlfa() * GE_PIover180);
        pDeb->SetV(vx, vy);
        vecObiekty.push_back(pDeb);
    }
}

void PlayerShip::Respawn(void)
{
    if (m_tiRespawn.inc(dt))
    {
        m_tiRespawn.reset();
        Respawning = false;
    }
    else
    {
        Respawning = true;
    }
}

void PlayerShip::AddBonus(BonusType bonusType)
{
    switch (bonusType)
    {
    case btBullets:
        puAddBullet.start();
        break;
    case btBulletSpeed:
        puBulletSpeed.start();
        break;
    }
}
} // namespace aster
