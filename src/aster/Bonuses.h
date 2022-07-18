#pragma once

#include <list>
#include "aster/BonusObject.hpp"
#include "aster/Types.h"

typedef std::list<BonusObject*> TvecBonus;
typedef std::list<BonusObject*>::iterator TvecBonusIt;

BonusObject* createBonusObject(const BonusType bonusType);
