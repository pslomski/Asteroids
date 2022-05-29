#include "Asteroid.h"
#include "Bullet.h"
#include "Bonuses.h"
#include "Sound.h"
#include "Tools.h"
#include "Consts.h"
#include "GameConsts.h"

namespace ge{

bool Asteroid::CreateBonus=true;

Asteroid::Asteroid(int in_iLevel)
:Object()
{
	ObjGeom=ogPolyg;
	HasBonus=false;
	color(GE_COLOR_ASTER);
	Level=in_iLevel;
	Create();
}

Asteroid::~Asteroid(void)
{
}

void Asteroid::Create(void)
{
	float Volume=1.0f;
	Float DegDelta, R;
	if(Level==1){
		ScoreValue=GE_SCRVAL_ASTER1;
		m_iSound=SND_ASTER_CRASH1;
		Volume=SND_VOL_ASTER_CRASH1;
		R=3.9;
		DegDelta=36.0;
		SetRotSpeed(rand()%60-120);
	}
	else if(Level==2){
		ScoreValue=GE_SCRVAL_ASTER2;
		m_iSound=SND_ASTER_CRASH2;
		Volume=SND_VOL_ASTER_CRASH2;
		R=2.8;
		DegDelta=52.0;
		SetRotSpeed(rand()%80-160);
	}
	else if(Level>=3){
		ScoreValue=GE_SCRVAL_ASTER3;
		m_iSound=SND_ASTER_CRASH3;
		Volume=SND_VOL_ASTER_CRASH3;
		R=1.7;
		DegDelta=72.0;
		SetRotSpeed(rand()%100-200);
	}

	sndCrash.Init(m_iSound, Volume);
	Verts.clear();
	for(Float deg=0.0; deg<310.0; deg+=DegDelta+(rand()%18-9)) {
		PointF pt;
		Float R2=R*(0.7+rand()%30/100.0);
		pt.x=R2*cos(deg*GE_PIover180);
		pt.y=R2*sin(deg*GE_PIover180);
		Verts.push_back(pt);
	}
	CalcBounds(Verts);

	glList=glGenLists(1);
 	glNewList(glList, GL_COMPILE);
	glColor3d(clr.r, clr.g, clr.b);
	glBegin(GL_LINE_LOOP);
	for(TvecPointFIt it=Verts.begin(); it!=Verts.end(); ++it){
		glVertex2d((*it).x, (*it).y);
	}
	glEnd();
	glEndList();
}

void Asteroid::OnRender(void)
{
	glCallList(glList);
}

BonusType GetBonusType()
{
	static BonusType btLast=btNone;
	static int RandCount=0;
	static int AsterCount=0;
	if(AsterCount<5){
		++AsterCount;
		return btNone;
	}
	int rnd=RAND(40);
	if(rnd<RandCount){
		RandCount=0;
		AsterCount=0;
		BonusType bt=BonusType(RAND(2));
		if(bt==btLast){
			switch(btLast){
				case btBullets: bt=btBulletSpeed; break; 
				case btBulletSpeed: bt=btBullets; break; 
			}
		}
		btLast=bt;
	 	return bt;
	}
	else{
		++RandCount;
	}
	return btNone;
}

void Asteroid::Crash(TvecAster& vecAster, TvecObiekt& vecDebris, TvecBonus& vecBonus)
{
	sndCrash.Play();

	int iDebCount, iAsterCount;
	Float LifeTime;
	BonusType BonusType=btNone;
	if(Level==1){
		iAsterCount=2;
		iDebCount=GE_ASTER1_DEBR_COUNT;
		LifeTime=1.1+rand()%7*0.1;
	}
	else if(Level==2){
		iAsterCount=2;
		iDebCount=GE_ASTER2_DEBR_COUNT;
		LifeTime=0.8+rand()%7*0.1;
		BonusType=btPoints;
	}
	else{
		iAsterCount=0;
		iDebCount=GE_ASTER3_DEBR_COUNT;
		LifeTime=0.5+rand()%7*0.1;
		BonusType=GetBonusType();
	}

	if(CreateBonus && BonusType!=btNone){
		TGEBonusObj *pBonus=geCreateBonusObj(BonusType);
		pBonus->SetXY(GetX(), GetY());
		pBonus->SetRandV(2.0, 3.0);
		vecBonus.push_back(pBonus);
	}

	for(int i=0; i<iAsterCount; ++i){
		Asteroid *pAster=new Asteroid(Level+1);
		if(i==0)
			pAster->HasBonus=HasBonus;//jeden fragment przejmuje bonus
		pAster->SetAlfa(GetAlfa()+i*180.0-90.0+rand()%50-25.0);
		Float x=GetX()+3.0*cos(pAster->GetAlfa()*GE_PIover180);
		Float y=GetY()+3.0*sin(pAster->GetAlfa()*GE_PIover180);
		pAster->SetXY(x, y);
		pAster->SetV(GetV()*1.3);
		vecAster.push_back(pAster);
	}

	for(int i=0; i<iDebCount; ++i){
		TAsterDebris *pDeb=new TAsterDebris;
		pDeb->SetAlfa(GetAlfa()+i*360.0/iDebCount+rand()%16-8.0);
		pDeb->SetXY(GetX(), GetY());
		pDeb->LifeTime.interval=LifeTime;
		Float vRand=5.0+rand()%15;
		Float vx=0.8*GetVX()+vRand*cos(pDeb->GetAlfa()*GE_PIover180);
		Float vy=0.8*GetVY()+vRand*sin(pDeb->GetAlfa()*GE_PIover180);
		pDeb->SetV(vx, vy);
		vecDebris.push_back(pDeb);
	}
}

}//namespace ge