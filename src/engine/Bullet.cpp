#include "Consts.h"
#include "Bullet.h"
#include "World.h"

TBullet::TBullet():
    TempObject()
{
    LifeTime.interval=1.0;
    Bounds.x0=-0.1;
    Bounds.x1= 0.1;
    Bounds.y0=-0.1;
    Bounds.y1= 0.1;
}

void TBullet::OnRender()
{
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3d(clr.r, clr.g, clr.b);
    glVertex2d(0.0, 0.0);
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////
//TShipDebris class implementation
//////////////////////////////////////////////////////////////////////////////////

TShipDebris::TShipDebris():
    TempObject()
{
    m_Ratio = 1.0;
    Float D = 0.15 + 0.1 * RAND(2);
    LifeTime.reset(1.3 + RAND(9) * 0.1);
    Bounds.x0 = -D;
    Bounds.x1 = D;
    Bounds.y0 = -D;
    Bounds.y1 = D;
    SetRotSpeed(720.0 + RAND(300));
}

void TShipDebris::Update(void)
{
    Object::update();
    m_Ratio = 1.0 - LifeTime.ratio();
}

void TShipDebris::OnRender(void)
{
    glColor3d(m_Ratio*clr.r, m_Ratio*clr.g, m_Ratio*clr.b);
    glBegin(GL_LINES);
    glVertex2d(Bounds.x0, 0.0);
    glVertex2d(Bounds.x1, 0.0);
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////
//TShipDebris class implementation
//////////////////////////////////////////////////////////////////////////////////

TAsterDebris::TAsterDebris():
    TempObject()
{
    LifeTime.reset(1.5 + RAND(9) * 0.1);
    Bounds.x0=-0.1;
    Bounds.x1= 0.1;
    Bounds.y0=-0.1;
    Bounds.y1= 0.1;
}

void TAsterDebris::Update(void)
{
    Object::update();
    m_Ratio=1.0-LifeTime.ratio();
}

void TAsterDebris::OnRender(void)
{
    glColor3d(m_Ratio*clr.r, m_Ratio*clr.g, m_Ratio*clr.b);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();
}

//////////////////////////////////////////////////////////////////////////////////
//TShipDebris class implementation
//////////////////////////////////////////////////////////////////////////////////

TStarBlink::TStarBlink():
    TempObject()
{
    color(1.0, 1.0, 1.0);
    Bounds.x0=-0.1;
    Bounds.x1= 0.1;
    Bounds.y0=-0.1;
    Bounds.y1= 0.1;
    Init();
}

void TStarBlink::Init()
{
    m_Size = RAND(2) + 1;
    LifeTime.reset(2.0 + RAND(30) * 0.1);
    SetXY(RAND(int(geWorld.getWidth())), RAND(int(geWorld.GetHeight())));
}

void TStarBlink::Update(void)
{
    if (Expired())
    {
        Init();
    };

    Object::update();
    m_Ratio = sin(LifeTime.ratio() * GE_PI);
}

void TStarBlink::OnRender(void)
{
    glColor3d(m_Ratio * clr.r, m_Ratio * clr.g, m_Ratio * clr.b);
    glPointSize(GLfloat(m_Size));
    glBegin(GL_POINTS);
    glVertex2d(0.0, 0.0);
    glEnd();
}
