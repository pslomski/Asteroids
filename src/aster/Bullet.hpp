#pragma once

#include <GL/gl.h>
#include <math.h>

#include "TempObject.hpp"

class TBullet : public TempObject
{
public:
    TBullet();

protected:
    void OnRender() override;
};

typedef std::list<TBullet *> TvecBullet;
typedef std::list<TBullet *>::iterator TvecBulletIt;
