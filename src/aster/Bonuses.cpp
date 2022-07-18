#include "aster/Bonuses.h"
#include "aster/BonusAddBullets.hpp"
#include "aster/BonusBulletSpeed.hpp"
#include "aster/BonusObject.hpp"
#include "aster/BonusPoints.hpp"
#include "aster/GameConsts.h"

BonusObject* createBonusObject(const BonusType bonusType)
{
    switch (bonusType)
    {
    case btBullets:
        return new TGEBonusAddBullets;
    case btBulletSpeed:
        return new TGEBonusBulletSpeed;
    case btPoints:
        return new TGEBonusPoints;
    }
    return new TGEBonusPoints;
}
