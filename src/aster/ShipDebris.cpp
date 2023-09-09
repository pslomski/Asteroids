#include "aster/ShipDebris.hpp"

namespace aster
{
ShipDebris::ShipDebris() : TempObject()
{
    ratio = 1.0;
    Float D = 0.15 + 0.1 * RAND(2);
    LifeTime.set(1.3 + RAND(9) * 0.1);
    bounds.x0 = -D;
    bounds.x1 = D;
    bounds.y0 = -D;
    bounds.y1 = D;
    SetRotSpeed(720.0 + RAND(300));
}

void ShipDebris::update()
{
    Object::update();
    ratio = 1.0 - LifeTime.ratio();
}

void ShipDebris::OnRender()
{
    glColor3d(ratio * clr.r, ratio * clr.g, ratio * clr.b);
    glBegin(GL_LINES);
    glVertex2d(bounds.x0, 0.0);
    glVertex2d(bounds.x1, 0.0);
    glEnd();
}
}
