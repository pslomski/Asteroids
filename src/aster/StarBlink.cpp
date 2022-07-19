#include "aster/StarBlink.hpp"

#include "aster/Consts.h"
#include "aster/World.h"

namespace aster
{
TStarBlink::TStarBlink() : TempObject()
{
    color(1.0, 1.0, 1.0);
    Bounds.x0 = -0.1;
    Bounds.x1 = 0.1;
    Bounds.y0 = -0.1;
    Bounds.y1 = 0.1;
    Init();
}

void TStarBlink::Init()
{
    size = RAND(2) + 1;
    LifeTime.reset(2.0 + RAND(30) * 0.1);
    SetXY(RAND(int(geWorld.getWidth())), RAND(int(geWorld.GetHeight())));
}

void TStarBlink::update()
{
    if (expired())
    {
        Init();
    };

    Object::update();
    ratio = sin(LifeTime.ratio() * GE_PI);
}

void TStarBlink::OnRender()
{
    glColor3d(ratio * clr.r, ratio * clr.g, ratio * clr.b);
    glPointSize(GLfloat(size));
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();
}
} // namespace aster
