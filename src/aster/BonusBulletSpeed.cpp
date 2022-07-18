#include "aster/BonusBulletSpeed.hpp"
#include "aster/GameConsts.h"

TGEBonusBulletSpeed::TGEBonusBulletSpeed() : BonusObject(btBulletSpeed)
{
    Create();
}

void TGEBonusBulletSpeed::Create()
{
    Float D = 0.5;
    color(GE_BONUS_BULLET_SPEED_COLOR);
    glList = glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-D, 4 * D);
    glVertex2d(2 * D, 4 * D);
    glVertex2d(0.5 * D, D);
    glVertex2d(2.5 * D, 2 * D);
    glVertex2d(-D, -4 * D);
    glVertex2d(0.0, 0.0);
    glVertex2d(-2 * D, -D);
    glEnd();
    glEndList();
}
