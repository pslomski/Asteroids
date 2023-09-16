#include "SoundSamplesBass.hpp"

namespace sound
{
SoundSamplesBass::~SoundSamplesBass()
{
    free();
}

#define MAX_CHANNEL_COUNT 5
void SoundSamplesBass::init()
{
    if(isLoaded)
    {
        return;
    }
    samples[SampleId::shipEngine]=BASS_SampleLoad(FALSE, "sound/ShipEngine.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL | BASS_SAMPLE_LOOP);
    samples[SampleId::shipFire]=BASS_SampleLoad(FALSE, "sound/ShipFire.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::shipCrash]=BASS_SampleLoad(FALSE, "sound/ShipCrash.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::asterCrash1]=BASS_SampleLoad(FALSE, "sound/AsterCrash1.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::asterCrash2]=BASS_SampleLoad(FALSE, "sound/AsterCrash2.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::asterCrash3]=BASS_SampleLoad(FALSE, "sound/AsterCrash3.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::ufoEngine]=BASS_SampleLoad(FALSE, "sound/UfoEngine.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL | BASS_SAMPLE_LOOP);
    samples[SampleId::startBeep]=BASS_SampleLoad(FALSE, "sound/StartBeep.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::bonusBeep]=BASS_SampleLoad(FALSE, "sound/BonusBeep.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::broom]=BASS_SampleLoad(FALSE, "sound/Broom.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::powerUp]=BASS_SampleLoad(FALSE, "sound/PowerUp.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    samples[SampleId::shipFirePower]=BASS_SampleLoad(FALSE, "sound/ShipFirePower.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    isLoaded = true;
}

void SoundSamplesBass::addSample(const SampleId sampleId, const char* name)
{
    samples
}

void SoundSamplesBass::free()
{
    if(isLoaded)
    {
        for(int i=0; i<NUM_BUFFERS; ++i){
            BASS_SampleFree(Sample[i]);
            Sample[i]=0;
        }
    }
    isLoaded = false;
}
} // namespace sound
