#pragma once

#include <gl\gl.h>
#include <math.h>

#include "TempObject.hpp"

class TBullet : public TempObject
{
public:
    TBullet();

protected:
    void OnRender();
};

typedef std::list<TBullet *> TvecBullet;
typedef std::list<TBullet *>::iterator TvecBulletIt;