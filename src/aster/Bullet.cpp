#include "aster/Consts.h"
#include "aster/Bullet.hpp"
#include "aster/World.h"

TBullet::TBullet() :
    TempObject()
{
    LifeTime.set(1.0);
    Bounds.x0 = -0.1;
    Bounds.x1 = 0.1;
    Bounds.y0 = -0.1;
    Bounds.y1 = 0.1;
}

void TBullet::OnRender()
{
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3d(clr.r, clr.g, clr.b);
    glVertex2d(0.0, 0.0);
    glEnd();
}
