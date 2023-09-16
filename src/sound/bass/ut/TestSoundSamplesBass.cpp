#include <gtest/gtest.h>

#include "sound/SoundSamples.hpp"
#include "sound/bass/SoundSamplesBass.hpp"

namespace testing
{
TEST(TestSoundSamplesBass, example)
{
    sound::SoundSamplesBass samples;
    samples.addSample(sound::SampleId::broom, "broom");
    ASSERT_EQ(samples.);
}
}
