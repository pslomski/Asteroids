#include "SoundEngineBass.hpp"

#include <stdlib.h>

#define MAX_CHANNEL_COUNT 5

SoundEngineBass::SoundEngineBass():
    SoundEngine()
{
    m_bSamplesLoaded=false;
    for(int i=0; i<NUM_BUFFERS; ++i) Sample[i]=0;
}

bool SoundEngineBass::Open()
{
    // Initialize the default output device with 3D support
    BASS_Init(-1,44100,BASS_DEVICE_3D,NULL,NULL);
    return InitSound();
}

void SoundEngineBass::Close()
{
    FreeSound();
    BASS_Free();
}

bool SoundEngineBass::InitSound()
{
    if(m_bSamplesLoaded) return true;
    
    Sample[SND_SHIP_ENGINE]=BASS_SampleLoad(FALSE, "sound/ShipEngine.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL | BASS_SAMPLE_LOOP);
    Sample[SND_SHIP_FIRE]=BASS_SampleLoad(FALSE, "sound/ShipFire.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    Sample[SND_SHIP_CRASH]=BASS_SampleLoad(FALSE, "sound/ShipCrash.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    Sample[SND_ASTER_CRASH1]=BASS_SampleLoad(FALSE, "sound/AsterCrash1.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    Sample[SND_ASTER_CRASH2]=BASS_SampleLoad(FALSE, "sound/AsterCrash2.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    Sample[SND_ASTER_CRASH3]=BASS_SampleLoad(FALSE, "sound/AsterCrash3.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    Sample[SND_UFO_ENGINE]=BASS_SampleLoad(FALSE, "sound/UfoEngine.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL | BASS_SAMPLE_LOOP);
    Sample[SND_START_BEEP]=BASS_SampleLoad(FALSE, "sound/StartBeep.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    Sample[SND_BONUS_BEEP]=BASS_SampleLoad(FALSE, "sound/BonusBeep.ogg", 0, 0, MAX_CHANNEL_COUNT, BASS_SAMPLE_OVER_VOL);
    Sample[SND_BROOM]=BASS_SampleLoad(FALSE, "sound/Broom.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    Sample[SND_POWERUP]=BASS_SampleLoad(FALSE, "sound/PowerUp.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);
    Sample[SND_SHIP_FIRE_POWER]=BASS_SampleLoad(FALSE, "sound/ShipFirePower.ogg", 0, 0, 1, BASS_SAMPLE_OVER_VOL);

    m_sndTest.Init(SND_SHIP_FIRE, SND_VOL_SHIP_FIRE);
    m_bSamplesLoaded=true;
    return true;
}

void SoundEngineBass::FreeSound()
{
    if(!m_bSamplesLoaded) return;
    for(int i=0; i<NUM_BUFFERS; ++i){
        BASS_SampleFree(Sample[i]);
        Sample[i]=0;
    }
    m_bSamplesLoaded=false;
}

void SoundEngineBass::SoundTest()
{
    m_sndTest.Play();
}

void SoundEngineBass::Play()
{
    HCHANNEL ch[MAX_CHANNEL_COUNT];
    DWORD iCount;
    for(int i=0; i<NUM_SOURCES; ++i){
        iCount=BASS_SampleGetChannels(Sample[i], ch);
        for(DWORD j=0; j<iCount; ++j){
            BASS_ChannelPlay(ch[j], !m_bPause);
        }
    }
    m_bPause=false;
}

void SoundEngineBass::Pause()
{

    HCHANNEL ch[MAX_CHANNEL_COUNT];
    DWORD iCount;
    for(int i=0; i<NUM_SOURCES; ++i){
        iCount=BASS_SampleGetChannels(Sample[i], ch);
        for(DWORD j=0; j<iCount; ++j){
            BASS_ChannelPause(ch[j]);
        }
    }
    m_bPause=true;
}

void SoundEngineBass::Stop()
{
    for(int i=0; i<NUM_SOURCES; ++i)
        BASS_SampleStop(Sample[i]);
    m_bPause=false;
}

void SoundEngineBass::SetVolume(float in_Vol)
{
    m_Volume=in_Vol;
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, DWORD(m_Volume*10000));	
}

void SoundEngineBass::Mute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, 0);
}

void SoundEngineBass::Unmute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, DWORD(m_Volume*10000));
}
