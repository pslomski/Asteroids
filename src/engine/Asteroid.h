#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Object.h"
#include "Bonuses.h"
#include <list>
#include "ObjectSound.h"

namespace ge{

#define ASTERVERTCOUNT 8

class Asteroid;

typedef std::list<Asteroid*> TvecAster;
typedef std::list<Asteroid*>::iterator TvecAsterIt;

class Asteroid:public Object
{
private:
	int m_iSound;
public:
	Asteroid(int in_iLevel);
	virtual ~Asteroid(void);
	void Create(void);
	void Crash(TvecAster& vecAster, TvecObiekt& vecDebris, TvecBonus& vecBonus);
	static bool CreateBonus;
	int Level;
	bool HasBonus;
	ObjectSoundBASS sndCrash;
protected:
	void OnRender(void);
};

}//namespace ge

#endif // _ASTEROID_H_