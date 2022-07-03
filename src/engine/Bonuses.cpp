#include "GameConsts.h"
#include "Bonuses.h"
#include "Sound.h"

TGEBonusObj::TGEBonusObj(BonusType in_Type):
    TempObject(GE_BONUS_LIFETIME),
    Type(in_Type)
{
    ScoreValue=GE_SCRVAL_BONUS;
    tiRot.reset(1.5);
    ObjGeom=ogPolyg;
    m_ColRatio=1.0;
    
    Float D=3.0;
    Verts.push_back(PointF(-D, -D));
    Verts.push_back(PointF( D, -D));
    Verts.push_back(PointF( D,  D));
    Verts.push_back(PointF(-D,  D));
    CalcBounds(Verts);
}

TGEBonusObj::~TGEBonusObj(void)
{
}

void TGEBonusObj::Update(void)
{
    Object::update();
    Float d{0.75};
    m_ColRatio = LifeTime.ratio();
    if(m_ColRatio < d)
    {
        m_ColRatio=1.0;
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

void TGEBonusObj::OnRender(void)
{
    glRotated(tiRot.ratio()*360.0, 0.0, 1.0, 0.0);
    glColor3d(m_ColRatio*clr.r, m_ColRatio*clr.g, m_ColRatio*clr.b);
    glCallList(glList);
}

////////////////////////////////////////////////////////////////////

TGEBonusBulletSpeed::TGEBonusBulletSpeed(void):
TGEBonusObj(btBulletSpeed)
{
    Create();
}

void TGEBonusBulletSpeed::Create(void)
{
    Float D=0.5;
    color(GE_BONUS_BULLET_SPEED_COLOR);
    glList=glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    glVertex2d(  -D, 4*D);
    glVertex2d( 2*D, 4*D);
    glVertex2d(0.5*D,   D);
    glVertex2d(2.5*D, 2*D);
    glVertex2d(  -D,-4*D);
    glVertex2d( 0.0, 0.0);
    glVertex2d(-2*D,  -D);
    glEnd();
    glEndList();
}

////////////////////////////////////////////////////////////////////

TGEBonusAddBullets::TGEBonusAddBullets(void):
TGEBonusObj(btBullets)
{
    Create();
}

void _DrawBullet(void)
{
    Float D=1.0;
    glBegin(GL_LINE_LOOP);
    glVertex2d( 0.0   , 2.00*D);//1
    glVertex2d( 0.25*D, 1.75*D);//2
    glVertex2d( 0.50*D, 1.00*D);//3
    glVertex2d( 0.50*D,-1.25*D);//4
    glVertex2d( 0.25*D,-1.50*D);//5
    glVertex2d( 0.50*D,-1.75*D);//6
    glVertex2d( 0.50*D,-2.00*D);//7
    glVertex2d(-0.50*D,-2.00*D);//8
    glVertex2d(-0.50*D,-1.75*D);//9
    glVertex2d(-0.25*D,-1.50*D);//10
    glVertex2d(-0.50*D,-1.25*D);//11
    glVertex2d(-0.50*D, 1.00*D);//12
    glVertex2d(-0.25*D, 1.75*D);//13
    glEnd();
}

void TGEBonusAddBullets::Create(void)
{
    color(GE_BONUS_ADD_BULLETS_COLOR);
    glList=glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glColor3d(clr.r, clr.g, clr.b);
    glRotated(31.0, 0.0, 0.0, 1.0);
    _DrawBullet();
    glEndList();			
}

////////////////////////////////////////////////////////////////////

TGEBonusPoints::TGEBonusPoints(void):
TGEBonusObj(btPoints)
{
    ScoreValue=GE_SCRVAL_BONUS;
    Create();
}

void TGEBonusPoints::Create(void)
{
    Float D=0.25;
    color(GE_BONUS_POINTS_COLOR);
    glList = glGenLists(1);
    glNewList(glList, GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2d( 2*D, 3*D);
    glVertex2d( 1*D, 4*D);
    glVertex2d(-1*D, 4*D);
    glVertex2d(-2*D, 3*D);
    glVertex2d(-2*D, 1*D);
    glVertex2d(-1*D, 0*D);
    glVertex2d( 1*D, 0*D);
    glVertex2d( 2*D,-1*D);
    glVertex2d( 2*D,-3*D);
    glVertex2d( 1*D,-4*D);
    glVertex2d(-1*D,-4*D);
    glVertex2d(-2*D,-3*D);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d(-0.5*D, 5*D);
    glVertex2d(-0.5*D,-5*D);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d( 0.5*D, 5*D);
    glVertex2d( 0.5*D,-5*D);
    glEnd();
    glEndList();
}

////////////////////////////////////////////////////////////////////

TGEBonusObj* geCreateBonusObj(BonusType in_Type)
{
    switch(in_Type){
    case btBullets: return new TGEBonusAddBullets;
    case btBulletSpeed: return new TGEBonusBulletSpeed;
    case btPoints: return new TGEBonusPoints;
    }//switch
    return new TGEBonusPoints;
}