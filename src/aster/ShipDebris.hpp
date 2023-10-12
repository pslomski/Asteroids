#pragma once

#include <GL/gl.h>
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
    void OnRender() override;

private:
    Float ratio;
};
} // namespace aster
