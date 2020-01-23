#pragma once

#ifndef TBULLET_H
#define TBULLET_H

#include <windows.h>
#include <math.h>
#include <gl\gl.h>
#include "Object.h"

class TBullet :public TTempObiekt {
public:
	TBullet();
	~TBullet() {}

protected:
	void OnRender(void);
};

typedef std::list<TBullet*> TvecBullet;
typedef std::list<TBullet*>::iterator TvecBulletIt;

class TShipDebris :public TTempObiekt
{
private:
	Float m_Ratio;
protected:
	void OnRender(void);
public:
	TShipDebris();
	~TShipDebris() {}
	void Update(void);
};

class TAsterDebris :public TTempObiekt
{
private:
	Float m_Ratio;
protected:
	void OnRender(void);
public:
	TAsterDebris();
	~TAsterDebris() {}
	void Update(void);
};

class TStarBlink :public TTempObiekt
{
private:
	Float m_Ratio;
	Float m_Size;
	void Init();
protected:
	void OnRender(void);
public:
	TStarBlink();
	~TStarBlink() {}
	void Update(void);
};

#endif //TBULLET_H

