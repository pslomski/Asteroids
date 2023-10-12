#include "aster/BonusObject.hpp"
#include "aster/GameConsts.h"

BonusObject::BonusObject(BonusType in_Type) : TempObject(GE_BONUS_LIFETIME), Type(in_Type)
{
    ScoreValue = GE_SCRVAL_BONUS;
    tiRot.set(1.5);
    ObjGeom = ogPolyg;
    m_ColRatio = 1.0;

    Float D = 3.0;
    Verts.push_back(PointF(-D, -D));
    Verts.push_back(PointF(D, -D));
    Verts.push_back(PointF(D, D));
    Verts.push_back(PointF(-D, D));
    CalcBounds(Verts);
}

BonusObject::~BonusObject() {}

void BonusObject::update()
{
    Object::update();
    Float d{0.75};
    m_ColRatio = LifeTime.ratio();
    if (m_ColRatio < d)
    {
        m_ColRatio = 1.0;
    }
    else
    {
        m_ColRatio = (1 - m_ColRatio) / (1 - d);
    }
    if (tiRot.inc(dt))
    {
        tiRot.reset();
    }
}

void BonusObject::OnRender()
{
    glRotated(tiRot.ratio() * 360.0, 0.0, 1.0, 0.0);
    glColor3d(m_ColRatio * clr.r, m_ColRatio * clr.g, m_ColRatio * clr.b);
    glCallList(glList);
}
