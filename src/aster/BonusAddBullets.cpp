#include "aster/BonusAddBullets.hpp"
#include "aster/GameConsts.h"

TGEBonusAddBullets::TGEBonusAddBullets() : BonusObject(btBullets)
{
    Create();
}

void _DrawBullet()
{
    Float D = 1.0;
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.0, 2.00 * D);        // 1
    glVertex2d(0.25 * D, 1.75 * D);   // 2
    glVertex2d(0.50 * D, 1.00 * D);   // 3
    glVertex2d(0.50 * D, -1.25 * D);  // 4
    glVertex2d(0.25 * D, -1.50 * D);  // 5
    glVertex2d(0.50 * D, -1.75 * D);  // 6
    glVertex2d(0.50 * D, -2.00 * D);  // 7
    glVertex2d(-0.50 * D, -2.00 * D); // 8
    glVertex2d(-0.50 * D, -1.75 * D); // 9
    glVertex2d(-0.25 * D, -1.50 * D); // 10
    glVertex2d(-0.50 * D, -1.25 * D); // 11
    glVertex2d(-0.50 * D, 1.00 * D);  // 12
    glVertex2d(-0.25 * D, 1.75 * D);  // 13
    glEnd();
}

void TGEBonusAddBullets::Create()
{
    color(GE_BONUS_ADD_BULLETS_COLOR);
    glList = glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glColor3d(clr.r, clr.g, clr.b);
    glRotated(31.0, 0.0, 0.0, 1.0);
    _DrawBullet();
    glEndList();
}
