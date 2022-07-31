#include "aster/BonusPoints.hpp"
#include "aster/GameConsts.h"
#include "aster/Tools.h"

TGEBonusPoints::TGEBonusPoints() : BonusObject(btPoints)
{
    ScoreValue = GE_SCRVAL_BONUS;
    Create();
}

void TGEBonusPoints::Create()
{
    Float D = 0.25;
    color(GE_BONUS_POINTS_COLOR);
    glList = glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2d(2 * D, 3 * D);
    glVertex2d(1 * D, 4 * D);
    glVertex2d(-1 * D, 4 * D);
    glVertex2d(-2 * D, 3 * D);
    glVertex2d(-2 * D, 1 * D);
    glVertex2d(-1 * D, 0 * D);
    glVertex2d(1 * D, 0 * D);
    glVertex2d(2 * D, -1 * D);
    glVertex2d(2 * D, -3 * D);
    glVertex2d(1 * D, -4 * D);
    glVertex2d(-1 * D, -4 * D);
    glVertex2d(-2 * D, -3 * D);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(-0.5 * D, 5 * D);
    glVertex2d(-0.5 * D, -5 * D);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(0.5 * D, 5 * D);
    glVertex2d(0.5 * D, -5 * D);
    glEnd();
    glEndList();
}
