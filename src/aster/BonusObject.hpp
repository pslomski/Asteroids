#pragma once

#include "aster/TempObject.hpp"

class BonusObject : public TempObject
{
public:
    BonusObject(BonusType in_Type);
    ~BonusObject();

    void update() override;

    BonusType Type;

protected:
    void OnRender() override;

private:
    TimeInterval tiRot;
    Float m_ColRatio;
};
