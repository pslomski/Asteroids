#pragma once

#ifndef TOBIEKT_H
#define TOBIEKT_H

#include <math.h>
#include <gl\gl.h>
#include <list>
#include "Types.h"
#include "Tools.h"

class Object {
public:
	Object();
	virtual ~Object() {
		if (glList)
			glDeleteLists(glList, 1);
	}

	friend Float geObDist(Object* pO1, Object* pO2);
	static Float dt; //krok czasowy
	GLint glList;//lista wyswietlania OpenGL
	TvecPointF Verts;
	ObjectGeom ObjGeom;
	Float xp, yp, alphap;//poplozenie w poprzednim kroku czasowym, (x-xp, y-yp) daje wektor przesuniecia
	int ScoreValue;

	void Move();
	BoxF Transform(BoxF& seg);
	bool CheckCollision(Object* pObiekt);
	void SetXY(Float ax, Float ay) {
		fx = ax;
		fy = ay;
		xp = ax;
		yp = ay;
	}
	void SetXY(PointF& pt) {
		fx = pt.x;
		fy = pt.y;
		xp = pt.x;
		yp = pt.y;
	}
	Float GetX(void) {
		return fx;
	}
	Float GetY(void) {
		return fy;
	}
	PointF GetXY(void) {
		return PointF(fx, fy);
	}
	void SetV(Float avx, Float avy) {
		fvx = avx;
		fvy = avy;
	}
	void SetV(Float av);
	void SetVA(Float av, Float alfa);
	void SetRandV(Float vmin, Float vmax);
	Float GetVX() {
		return fvx;
	}
	Float GetVY() {
		return fvy;
	}
	Float GetV() {
		return sqrt(fvx * fvx + fvy * fvy);
	}
	void SetA(Float aa);
	Float GetA() {
		return fa;
	}
	void SetAlfa(Float aalfa) {
		falfa = CorrectAlfa(aalfa);
		alphap = falfa;
	}
	Float GetAlfa() {
		return falfa;
	}
	Float GetRotSpeed(void) {
		return fomega;
	}
	void SetRotSpeed(Float omega) {
		fomega = omega;
	}
	void color(Float aRed = 1, Float aGreen = 1, Float aBlue = 1) {
		clr.r = aRed;
		clr.g = aGreen;
		clr.b = aBlue;
	}
	void color(Color& in_clr) {
		clr = in_clr;
	}
	virtual void Update() {
		Move();
	}
	virtual void Draw();
	virtual bool Expired() {
		return false;
	}
	void Render();
protected:
	Float KDec; //wspolczynnik oporu. Powoduje hamowanie
	Color clr;
	Bounds Bounds;
	virtual void OnRender() = 0;//rysuje obiekt we wsp. wlasnych obiektu
	Float CorrectAlfa(Float alfa);
	void CalcBounds(TvecPointF& Verts);
private:
	Float falfa; //kat w plaszczyznie xy
	Float fomega; //predkosc katowa
	Float fx, fy; //skladowe polozenia
	Float fvx, fvy; //skladowe predkosci
	Float fv;//  wartosc wektora predkosci
	Float fax, fay; //skladowe przyspieszenia
	Float fa; //przyspieszenie
};

typedef std::list<Object*> TvecObiekt;
typedef std::list<Object*>::iterator TvecObiektIt;

////////////////////////////////////////////////
//obiekt ktory ma znikac po pewnym czasie

class TTempObiekt :public Object
{
public:
	TTempObiekt();
	TTempObiekt(Float in_LifeTime);
	~TTempObiekt() {}
	bool Expired();
	void SetExpired();

	TimeInterval LifeTime;
};

#endif //TOBIEKT_H

