#pragma once

#include <gl\gl.h>

#include "TempObject.hpp"

namespace aster
{
class TStarBlink : public TempObject
{
public:
    TStarBlink();
    void update() override;

protected:
    void OnRender() override;

private:
    Float ratio;
    Float size;
    void Init();
};
} // namespace aster
