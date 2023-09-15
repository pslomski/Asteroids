#pragma once

#include "Bullet.hpp"
#include "Object.h"
#include "sound/Sound.hpp"

class TUfo :public Object
{
public:
    TUfo();
    ~TUfo();

    void update() override;
    Object *pShip;
    Object *pAster;
    void Action(TvecBullet& vecBullet);
    TBullet* FireBullet(const PointF &pt);
    void Crash(TvecObiekt &vecObiekty);
    TGEObjectSound sndEngine;
    TGEObjectSound sndCrash;

protected:
    void OnRender() override;

private:
    Float CheckTime;
    Float CheckTimeElapsed;
    Float MoveTime;
    Float MoveTimeElapsed;
    Float FireTime;
    Float FireTimeElapsed;
};
