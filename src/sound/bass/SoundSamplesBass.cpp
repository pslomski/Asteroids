#include "SoundSamplesBass.hpp"
#include <sstream>
#include "bass.h"
#include "sound/SoundSamples.hpp"

namespace sound
{
SoundSamplesBass::~SoundSamplesBass()
{
    free();
}

void SoundSamplesBass::init()
{
    if (samples.size() == 0)
    {
        addSample(SampleId::shipEngine, "ShipEngine", FLAG_SAMPLE_LOOP);
        addSample(SampleId::shipFire, "ShipFire");
        addSample(SampleId::shipCrash, "ShipCrash");
        addSample(SampleId::asterCrash1, "AsterCrash1");
        addSample(SampleId::asterCrash2, "AsterCrash2");
        addSample(SampleId::asterCrash3, "AsterCrash3");
        addSample(SampleId::ufoEngine, "UfoEngine", FLAG_SAMPLE_LOOP);
        addSample(SampleId::startBeep, "StartBeep");
        addSample(SampleId::bonusBeep, "BonusBeep");
        addSample(SampleId::broom, "Broom");
        addSample(SampleId::powerUp, "PowerUp");
        addSample(SampleId::shipFirePower, "ShipFirePower");
    }
}

DWORD getBassFlags(const Flags flags)
{
    DWORD bassFlags{BASS_SAMPLE_OVER_POS};
    if (flags & FLAG_SAMPLE_LOOP)
    {
        bassFlags |= BASS_SAMPLE_LOOP;
    }
    if (flags & FLAG_SAMPLE_OVER_VOL)
    {
        bassFlags |= BASS_SAMPLE_OVER_VOL;
    }
    return bassFlags;
}

void SoundSamplesBass::addSample(const SampleId sampleId, const char* name, const Flags flags)
{
    constexpr DWORD maxChannelCount = 5;
    constexpr auto subdir{"sound/"};
    constexpr auto ext{".ogg"};
    std::stringstream ss{};
    ss << subdir << name << ext;
    samples[sampleId] = BASS_SampleLoad(FALSE, ss.str().c_str(), 0, 0, maxChannelCount, getBassFlags(flags));
}

void SoundSamplesBass::playSample(const SampleId sampleId) {}

void SoundSamplesBass::free()
{
    for (auto sample : samples)
    {
        BASS_SampleFree(sample.second);
    }
    samples.clear();
}
} // namespace sound
