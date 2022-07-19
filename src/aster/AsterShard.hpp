#pragma once

#include <gl\gl.h>
#include <math.h>

#include "TempObject.hpp"

namespace aster
{
class AsterShard : public TempObject
{
public:
    AsterShard();
    void update() override;

protected:
    void OnRender() override;

private:
    Float ratio;
};
} // namespace aster
