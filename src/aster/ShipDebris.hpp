#pragma once

#include <gl\gl.h>
#include <math.h>

#include "TempObject.hpp"

namespace aster
{
class ShipDebris : public TempObject
{
public:
    ShipDebris();
    void update() override;

protected:
    void OnRender();

private:
    Float ratio;
};
}
