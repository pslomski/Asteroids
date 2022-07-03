#pragma once
#include "engine/TempObject.hpp"
#include "engine/Tools.h"

class TGEBonusObj: public TempObject
{
private:
    TimeInterval tiRot;
    Float m_ColRatio;
public:
    BonusType Type;
    TGEBonusObj(BonusType in_Type);
    virtual ~TGEBonusObj(void);
    void Update(void);
    void OnRender(void);
};

/////////////////////////////////////////////

class TGEBonusBulletSpeed: public TGEBonusObj
{
public:
    TGEBonusBulletSpeed(void);
private:
    void Create(void);
};

/////////////////////////////////////////////

class TGEBonusAddBullets:public TGEBonusObj
{
public:
    TGEBonusAddBullets(void);
private:
    void Create(void);
};

/////////////////////////////////////////////

class TGEBonusPoints:public TGEBonusObj
{
public:
    TGEBonusPoints(void);
private:
    void Create(void);
};

/////////////////////////////////////////////

typedef std::list<TGEBonusObj*> TvecBonus;
typedef std::list<TGEBonusObj*>::iterator TvecBonusIt;

TGEBonusObj* geCreateBonusObj(BonusType in_Type);
