#pragma once
#include <gl\gl.h>
#include <math.h>

#include "TempObject.hpp"

class TBullet :public TempObject
{
public:
    TBullet();
    ~TBullet() {}

protected:
    void OnRender(void);
};

typedef std::list<TBullet*> TvecBullet;
typedef std::list<TBullet*>::iterator TvecBulletIt;

class TShipDebris: public TempObject
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

class TAsterDebris: public TempObject
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

class TStarBlink: public TempObject
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
