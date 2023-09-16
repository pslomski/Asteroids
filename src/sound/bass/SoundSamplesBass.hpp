#pragma once

#include <map>
#include <bass.h>

#include "sound/SoundSamples.hpp"

namespace sound
{
class SoundSamplesBass: public SoundSamples
{
public:
    ~SoundSamplesBass();
    void init() override;
    void free() override;

private:
    using Samples = std::map<SampleId, HSAMPLE>;
    void addSample(const SampleId sampleId, const char* name);
    Samples samples;
    bool isLoaded{false};
};
} // namespace sound
