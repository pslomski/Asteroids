#include "Consts.h"
#include "Bullet.h"
#include "World.h"

TBullet::TBullet()
:TTempObiekt()
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

TShipDebris::TShipDebris()
:TTempObiekt()
{
	m_Ratio=1.0;
	Float D=0.15+0.1*RAND(2);
	LifeTime.interval=1.3+rand()%9*0.1;
	Bounds.x0=-D;
	Bounds.x1= D;
	Bounds.y0=-D;
	Bounds.y1= D;
	SetRotSpeed(720.0+RAND(300));
}

void TShipDebris::Update(void)
{
	Object::Update();
	m_Ratio=1.0-LifeTime.Ratio();
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

TAsterDebris::TAsterDebris()
:TTempObiekt()
{
	LifeTime.interval=1.5+rand()%9*0.1;
	Bounds.x0=-0.1;
	Bounds.x1= 0.1;
	Bounds.y0=-0.1;
	Bounds.y1= 0.1;
}

void TAsterDebris::Update(void)
{
	Object::Update();
	m_Ratio=1.0-LifeTime.Ratio();
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

TStarBlink::TStarBlink()
:TTempObiekt()
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
	m_Size=RAND(2)+1;
	LifeTime.Reset();
	LifeTime.interval=2.0+RAND(30)*0.1;
	SetXY(RAND(int(geWorld.getWidth())), RAND(int(geWorld.GetHeight())));
}

void TStarBlink::Update(void)
{
	if (Expired()){
		Init();
	};

	Object::Update();
	m_Ratio=sin(LifeTime.Ratio()*GE_PI);
}

void TStarBlink::OnRender(void)
{
	glColor3d(m_Ratio*clr.r, m_Ratio*clr.g, m_Ratio*clr.b);
	glPointSize(GLfloat(m_Size));
	glBegin(GL_POINTS);
	glVertex2d(0.0, 0.0);
	glEnd();
}
