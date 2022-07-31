#pragma once

#include <list>
#include "Bonuses.h"
#include "Object.h"
#include "ObjectSound.h"

namespace aster
{
#define ASTERVERTCOUNT 8

class Asteroid;

typedef std::list<Asteroid *> TvecAster;
typedef std::list<Asteroid *>::iterator TvecAsterIt;

class Asteroid : public Object
{
private:
    int m_iSound;

public:
    Asteroid(int in_iLevel);

    void Create();
    void Crash(TvecAster &vecAster, TvecObiekt &vecDebris, TvecBonus &vecBonus);
    static bool CreateBonus;
    int Level;
    bool HasBonus;
    ObjectSoundBASS sndCrash;

protected:
    void OnRender() override;
};
} // namespace aster
