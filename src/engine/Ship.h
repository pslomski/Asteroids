#pragma once
#include <math.h>
#include <gl\gl.h>
#include "Tools.h"
#include "Object.h"
#include "Bullet.h"
#include "ObjectSound.h"


class PlayerShip;

class PowerUp {
public:
    PowerUp(Float dt);
    TimeInterval duration;
    void Start(void);
    void Stop(void);
    bool IsActive()
    {
        return isActive;
    }
protected:
    virtual void OnStart(void) = 0;
    virtual void OnStop(void) = 0;
    bool isActive;
};

class PowerUpAddBullet: public PowerUp {
public:
    PowerUpAddBullet(Float dt) : PowerUp(dt) {};
    PlayerShip* pShip;
protected:
    void OnStart(void);
    void OnStop(void);
};

class PowerUpBulletSpeed: public PowerUp {
public:
    PowerUpBulletSpeed(Float in_Dutation) : PowerUp(in_Dutation) {};
    PlayerShip* pShip;
protected:
    void OnStart(void);
    void OnStop(void);
};

class PlayerShip: public Object
{
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
protected:
    void OnRender(void);
public:
    PlayerShip(Float ax, Float ay, Float aangle);
    ~PlayerShip();

    void Update(void);
    Float BulletSpeed;
    bool Respawning;
    unsigned int MaxBullets;
    void AccelerationOn();
    void AccelerationOff();
    void RotateLeft();
    void RotateRight();
    void RotateLeftStop()
    {
        m_tiRotateLeft.reset();
    }

    void RotateRightStop(void)
    {
        m_tiRotateRight.reset();
    }

    TBullet* FireBullet();
    void Crash(TvecObiekt& vecObiekty);
    void Respawn(void);
    void AddBonus(BonusType in_Type);
    PowerUpAddBullet puAddBullet; 
    PowerUpBulletSpeed puBulletSpeed;
    TGEObjectSound sndFire;
    TGEObjectSound sndFirePow;
    TGEObjectSound sndEngine;
    TGEObjectSound sndCrash;
};
