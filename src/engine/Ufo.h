#pragma once
#include "Object.h"
#include "Bullet.h"
#include "ObjectSound.h"

class TUfo :public Object
{
private:
	Float CheckTime;
	Float CheckTimeElapsed;
	Float MoveTime;
	Float MoveTimeElapsed;
	Float FireTime;
	Float FireTimeElapsed;
	
protected:
	void OnRender(void);
public:
	TUfo(void);
	virtual ~TUfo(void);
	void Update(void);
	Object *pShip;//wskaznik na statek gracza (ustawiane przy okazji poruszania obiektow)
	Object *pAster;//wskaznik na najblizsza asteroide (ustawiane przy okazji poruszania obiektow)
	void Action(TvecBullet& vecBullet);
	TBullet* FireBullet(PointF &pt);
	void Crash(TvecObiekt &vecObiekty);
	TGEObjectSound sndEngine;
	TGEObjectSound sndCrash;
};
