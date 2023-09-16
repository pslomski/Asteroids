#pragma once

#include <bass.h>

namespace sound
{
enum class SampleId
{
    shipEngine,
    shipFire,
    shipCrash,
    asterCrash1,
    asterCrash2,
    asterCrash3,
    ufoEngine,
    startBeep,
    bonusBeep,
    broom,
    powerUp,
    shipFirePower,
    size
};

class SoundSamples
{
public:
    virtual ~SoundSamples() = 0;
    virtual void init() = 0;
    virtual void free() = 0;
};
} // namespace sound
