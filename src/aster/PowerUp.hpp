#pragma once

#include "aster/TimeInterval.hpp"

namespace aster
{
class PowerUp
{
public:
    PowerUp(const Float timeSpanSec);
    virtual ~PowerUp(){};

    void start();
    void stop();
    bool isActive() const;

    TimeInterval duration;

protected:
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    bool active;
};
} // namespace aster
