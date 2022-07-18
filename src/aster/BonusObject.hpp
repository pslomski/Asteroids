#pragma once

#include "aster/TempObject.hpp"

class BonusObject: public TempObject
{
private:
    TimeInterval tiRot;
    Float m_ColRatio;
public:
    BonusType Type;
    BonusObject(BonusType in_Type);
    ~BonusObject();
    void Update();
    void OnRender();
};
