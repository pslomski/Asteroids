#pragma once
#include <gl\gl.h>
#include <math.h>

#include "TempObject.hpp"

class TBullet : public TempObject
{
public:
    TBullet();
    ~TBullet() {}

protected:
    void OnRender();
};

typedef std::list<TBullet *> TvecBullet;
typedef std::list<TBullet *>::iterator TvecBulletIt;

class TShipDebris : public TempObject
{
private:
    Float m_Ratio;

protected:
    void OnRender();

public:
    TShipDebris();
    ~TShipDebris() {}
    void Update();
};

class TAsterDebris : public TempObject
{
private:
    Float m_Ratio;

protected:
    void OnRender(void);

public:
    TAsterDebris();
    ~TAsterDebris() {}
    void Update();
};

class TStarBlink : public TempObject
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
