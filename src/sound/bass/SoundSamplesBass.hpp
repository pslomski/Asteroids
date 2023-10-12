#pragma once

#include <bass.h>
#include <map>

#include "sound/SoundSamples.hpp"

namespace sound
{
class SoundSamplesBass : public SoundSamples
{
public:
    ~SoundSamplesBass();
    void init() override;
    void free() override;
    void addSample(const SampleId sampleId, const char* name, const Flags flags = 0) override;
    void playSample(const SampleId sampleId) override;

private:
    using Samples = std::map<SampleId, HSAMPLE>;
    Samples samples;
};
} // namespace sound
