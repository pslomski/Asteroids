#pragma once

#include <bass.h>
#include <cstdint>

namespace sound
{
using Flags = uint32_t;

constexpr Flags FLAG_SAMPLE_LOOP = 0x00000001;
constexpr Flags FLAG_SAMPLE_OVER_VOL = 0x00000002;

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
    virtual ~SoundSamples(){};
    virtual void init() = 0;
    virtual void free() = 0;
    virtual void addSample(const SampleId sampleId, const char* name, const Flags flags = 0) = 0;
    virtual void playSample(const SampleId sampleId) = 0;
};
} // namespace sound
