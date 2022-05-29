#include "Ufo.h"
#include "Sound.h"
#include "Consts.h"
#include "GameConsts.h"

TUfo::TUfo(void)
:Object()
{
	sndEngine.Init(SND_UFO_ENGINE, SND_VOL_UFO_ENGINE);
	sndCrash.Init(SND_ASTER_CRASH2, SND_VOL_ASTER_CRASH2);
	ScoreValue=GE_SCRVAL_UFO;
	ObjGeom=ogPolyg;
	pShip=NULL;
	pAster=NULL;
	CheckTime=0.7;
	CheckTimeElapsed=0.0;
	MoveTime=3.0;
	MoveTimeElapsed=0.0;
	FireTime=2.0;
	FireTimeElapsed=0.0;
	color(GE_UFO_COLOR);
	SetRandV(10.0, 15.0);

	Verts.push_back(PointF( 2.0, 0.0));
	Verts.push_back(PointF( 0.8,-0.75));
	Verts.push_back(PointF(-0.8,-0.75));
	Verts.push_back(PointF(-2.0, 0.0));
	Verts.push_back(PointF(-0.8, 0.75));
	Verts.push_back(PointF( 0.8, 0.75));
	Verts.push_back(PointF( 2.0, 0.0));
	CalcBounds(Verts);

	sndEngine.Play();
}

TUfo::~TUfo(void)
{
	sndEngine.Stop();
}

void TUfo::Update(void)
{
	Object::Update();
	/*ALfloat Pos[]={ALfloat(GetX()), ALfloat(GetY()), 0.0f};
	ALfloat Vel[]={ALfloat(GetV()), ALfloat(GetV()), 0.0f};
	alSourcefv(geSound.Src[SND_UFO_ENGINE], AL_POSITION, Pos);
	alSourcefv(geSound.Src[SND_UFO_ENGINE], AL_VELOCITY, Vel);*/
}

void TUfo::OnRender(void)
{
	glColor3d(clr.r, clr.g, clr.b);

	glBegin(GL_LINE_LOOP);
	for(TvecPointFIt it=Verts.begin(); it!=Verts.end(); ++it) glVertex2d((*it).x, (*it).y);
	glEnd();
}

void TUfo::Action(TvecBullet& vecBullet)
{
	const Float SafeDist=12.0;

	CheckTimeElapsed+=dt;
	if(CheckTimeElapsed>CheckTime){
		CheckTimeElapsed=0.0;
		Float RShp=2e6;
		Float RAst=1e6;
		if(pShip) RShp=geObDist(this, pShip);
		if(pAster) RAst=geObDist(this, pAster);
		if((RShp<SafeDist) || (RAst<SafeDist))
			MoveTimeElapsed=MoveTime;

	}

	MoveTimeElapsed+=dt;
	if(MoveTimeElapsed>MoveTime){
		Float RShp=2e6;
		Float RAst=1e6;
		if(pShip) RShp=geObDist(this, pShip);
		if(pAster) RAst=geObDist(this, pAster);
		if(pShip && RShp<SafeDist){
			int sgn=rand()%2 ? -1 : 1;
			SetVA(10.0, pShip->GetAlfa()+90*sgn);		
		}
		if(pAster && RAst<SafeDist){
			int sgn=rand()%2 ? -1 : 1;
			SetVA(10.0, pAster->GetAlfa()+90*sgn);
		}
		else{
			SetRandV(9.0, 13.0);
		}
		Float x=GetX()+GetVX();
		Float y=GetY()+GetVY();
		vecBullet.push_back(FireBullet(PointF(x, y)));//prewencyjny strzal w nowyn kierunku ruchu
		FireTimeElapsed=0.0;
		MoveTimeElapsed=0.0;
	}

	FireTimeElapsed+=dt;
	if(FireTimeElapsed>FireTime){
		Float RShp=2e6;
		Float RAst=1e6;
		if(pShip) RShp=geObDist(this, pShip);
		if(pAster) RAst=geObDist(this, pAster);
		if(RShp<RAst){
			if(pShip && RShp<35.0){
				vecBullet.push_back(FireBullet(pShip->GetXY()));
			}
		}
		else{
			if(pAster && RAst<20.0){
				vecBullet.push_back(FireBullet(pAster->GetXY()));
			}
		}
		FireTimeElapsed=0.0;
	}
}

TBullet* TUfo::FireBullet(const PointF &pt)
{
	Float Speed=22.0;
	TBullet *bullet=new TBullet;
	bullet->LifeTime.interval=3.0;
	bullet->SetXY(GetX(), GetY());
	Float alfa=atan2(pt.y-GetY(), pt.x-GetX())*GE_180overPI;
	bullet->SetAlfa(alfa+rand()%6-3);
	bullet->SetV(Speed);
	bullet->color(clr.r, clr.g, clr.b);
	return bullet;
}

void TUfo::Crash(TvecObiekt &vecObiekty)
{
/*	ALfloat Pos[]={ALfloat(GetX()), ALfloat(GetY()), 0.0f};
	ALfloat Vel[]={ALfloat(GetV()), ALfloat(GetV()), 0.0f};
	alSourcefv(geSound.Src[SND_ASTER_CRASH2], AL_POSITION, Pos);
	alSourcefv(geSound.Src[SND_ASTER_CRASH2], AL_VELOCITY, Vel);
	alSourcef (geSound.Src[SND_ASTER_CRASH2], AL_PITCH, ALfloat(0.7+0.1*RAND(3)));
	geSound.PlaySound(SND_ASTER_CRASH2, SND_VOL_ASTER_CRASH2);*/
	sndCrash.Play();

	int iDebCount=GE_UFO_DEBR_COUNT;
	for(int i=0; i<iDebCount; ++i){
		TAsterDebris *pDeb=new TAsterDebris;
		pDeb->color(clr);
		pDeb->SetAlfa(GetAlfa()+i*360.0/iDebCount+rand()%16-8.0);
		pDeb->SetXY(GetX(), GetY());
		Float vRand=3.0+rand()%15;
		Float vx=0.8*GetVX()+vRand*cos(pDeb->GetAlfa()*GE_PIover180);
		Float vy=0.8*GetVY()+vRand*sin(pDeb->GetAlfa()*GE_PIover180);
		pDeb->SetV(vx, vy);
		pDeb->SetRotSpeed(rand()/200-400);
		vecObiekty.push_back(pDeb);
	}
}