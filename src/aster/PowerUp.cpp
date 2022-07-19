#include "aster/PowerUp.hpp"

namespace aster
{
PowerUp::PowerUp(const Float timeSpanSec) :
    active(false)
{
    duration.set(timeSpanSec);
}

bool PowerUp::isActive() const
{
    return active;
}

void PowerUp::start()
{
    stop();
    onStart();
    active = true;
}

void PowerUp::stop()
{
    if (active)
    {
        onStop();
    }
    duration.reset();
    active = false;
}
} // namespace aster
