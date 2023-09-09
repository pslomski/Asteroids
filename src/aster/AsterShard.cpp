#include "aster/AsterShard.hpp"

namespace aster
{
AsterShard::AsterShard() : TempObject()
{
    LifeTime.set(1.5 + RAND(9) * 0.1);
    bounds.x0 = -0.1;
    bounds.x1 = 0.1;
    bounds.y0 = -0.1;
    bounds.y1 = 0.1;
}

void AsterShard::update()
{
    Object::update();
    ratio = 1.0 - LifeTime.ratio();
}

void AsterShard::OnRender()
{
    glColor3d(ratio * clr.r, ratio * clr.g, ratio * clr.b);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();
}
} // namespace aster
