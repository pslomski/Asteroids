#pragma once

#include <gl\gl.h>
#include <math.h>

#include "Tools.h"
#include "Object.h"
#include "ObjectSound.h"
#include "aster/Bullet.hpp"
#include "aster/PowerUpAddBullet.hpp"
#include "aster/PowerUpBulletSpeed.hpp"

namespace aster
{
class PlayerShip: public Object
{
public:
    PlayerShip(Float ax, Float ay, Float aangle);
    ~PlayerShip();

    void update() override;
    void AccelerationOn();
    void AccelerationOff();
    void RotateLeft();
    void RotateRight();
    void RotateLeftStop()
    {
        m_tiRotateLeft.reset();
    }

    void RotateRightStop()
    {
        m_tiRotateRight.reset();
    }

    TBullet* FireBullet();
    void Crash(TvecObiekt&);
    void Respawn();
    void AddBonus(BonusType);

    PowerUpAddBullet puAddBullet; 
    PowerUpBulletSpeed puBulletSpeed;
    TGEObjectSound sndFire;
    TGEObjectSound sndFirePow;
    TGEObjectSound sndEngine;
    TGEObjectSound sndCrash;
    Float BulletSpeed;
    bool Respawning;
    unsigned int MaxBullets;

protected:
    void OnRender() override;

private:
    Color m_clrTmp;
    Float m_BoostLen;
    Float Accel, AccelBurst, AccelMax; // ship acceleration
    Float m_RotSpeed;
    Float m_RespBlinkColRatio;
    bool faccelerated;
    bool fshield;
    bool bDarken; // okresowe przyciemnianie koloru
    Float sndEngineGain;
    bool EngSndStopped;
    Color clEngine;
    TimeInterval m_tiAccel;
    TimeInterval m_tiFade;
    TimeInterval m_tiEngineBlink;
    TimeInterval m_tiRotateLeft, m_tiRotateRight;
    TimeInterval m_tiRespawnBlink;
    TimeInterval m_tiRespawn;
};
} // namespace aster
