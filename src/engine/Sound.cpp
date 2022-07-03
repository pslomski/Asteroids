#include "Sound.h"
#include <stdlib.h>
#include "World.h"

SoundEngineBASS geSound;
TGEMusicEngineBASS geMusic;

#define MAX_CHANNEL_COUNT 5

SoundEngineBASS::SoundEngineBASS(void):
    SoundEngine()
{
    m_bSamplesLoaded=false;
    for(int i=0; i<NUM_BUFFERS; ++i) Sample[i]=0;
}

bool SoundEngineBASS::Open(void)
{
    // Initialize the default output device with 3D support
    BASS_Init(-1,44100,BASS_DEVICE_3D,NULL,NULL);
    return InitSound();
}

void SoundEngineBASS::Close(void)
{
    FreeSound();
    BASS_Free();
}

bool SoundEngineBASS::InitSound(void)
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

void SoundEngineBASS::FreeSound(void)
{
    if(!m_bSamplesLoaded) return;
    for(int i=0; i<NUM_BUFFERS; ++i){
        BASS_SampleFree(Sample[i]);
        Sample[i]=0;
    }
    m_bSamplesLoaded=false;
}

void SoundEngineBASS::SoundTest(void)
{
    m_sndTest.Play();
}

void SoundEngineBASS::Play()
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

void SoundEngineBASS::Pause()
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

void SoundEngineBASS::Stop()
{
    for(int i=0; i<NUM_SOURCES; ++i)
        BASS_SampleStop(Sample[i]);
    m_bPause=false;
}

void SoundEngineBASS::SetVolume(float in_Vol)
{
    m_Volume=in_Vol;
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, DWORD(m_Volume*10000));	
}

void SoundEngineBASS::Mute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, 0);
}

void SoundEngineBASS::Unmute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, DWORD(m_Volume*10000));
}

/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_OPENAL

TGESoundEngineOAL::TGESoundEngineOAL(void):
    TGESoundEngineBase()
{
    m_bSamplesLoaded=false;
    for(int i=0; i<NUM_BUFFERS; ++i) Buf[i]=0;
    for(int i=0; i<NUM_SOURCES; ++i) Src[i]=0;
}

bool TGESoundEngineOAL::Open(void)
{
    alutInit(NULL, 0);
    return InitSound();
}

void TGESoundEngineOAL::Close(void)
{
    FreeSound();
    alutExit();
}

void TGESoundEngineOAL::StopAllSounds(void)
{
    for(int i=0; i<NUM_SOURCES; ++i) alSourceStop(Src[i]);
}

bool TGESoundEngineOAL::InitSound(void)
{
    if(m_bSamplesLoaded) return true;
    Buf[SND_SHIP_ENGINE]=alutCreateBufferFromFile("sound/ShipEngine.wav");
    Buf[SND_SHIP_FIRE]=alutCreateBufferFromFile("sound/ShipFire.wav");
    Buf[SND_SHIP_CRASH]=alutCreateBufferFromFile("sound/ShipCrash.wav");
    Buf[SND_ASTER_CRASH1]=alutCreateBufferFromFile("sound/AsterCrash1.wav");
    Buf[SND_ASTER_CRASH2]=alutCreateBufferFromFile("sound/AsterCrash2.wav");
    Buf[SND_ASTER_CRASH3]=alutCreateBufferFromFile("sound/AsterCrash3.wav");
    Buf[SND_UFO_ENGINE]=alutCreateBufferFromFile("sound/UfoEngine.wav");
    Buf[SND_START_BEEP]=alutCreateBufferFromFile("sound/StartBeep.wav");
    Buf[SND_BONUS_BEEP]=alutCreateBufferFromFile("sound/BonusBeep.wav");
    Buf[SND_BROOM]=alutCreateBufferFromFile("sound/Broom.wav");
    Buf[SND_POWERUP]=alutCreateBufferFromFile("sound/PowerUp.wav");
    Buf[SND_SHIP_FIRE_POWER]=alutCreateBufferFromFile("sound/ShipFirePower.wav");
    
// Bind the buffer with the source.
    alGenSources(NUM_SOURCES, Src);
    if(alGetError()!=AL_NO_ERROR) return false;

    ALfloat RefDist=ALfloat(geWorld.GetWidth()/8.0);
    ALfloat MaxDist=ALfloat(2.0*RefDist);
    alSourcei(Src[SND_SHIP_ENGINE], AL_BUFFER, Buf[SND_SHIP_ENGINE]);
    alSourcei(Src[SND_SHIP_ENGINE], AL_LOOPING, AL_TRUE);
    alSourcef(Src[SND_SHIP_ENGINE], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_SHIP_ENGINE], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_SHIP_FIRE], AL_BUFFER, Buf[SND_SHIP_FIRE]);
    alSourcef(Src[SND_SHIP_FIRE], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_SHIP_FIRE], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_SHIP_CRASH], AL_BUFFER, Buf[SND_SHIP_CRASH]);
    alSourcef(Src[SND_SHIP_CRASH], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_SHIP_CRASH], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_ASTER_CRASH1], AL_BUFFER, Buf[SND_ASTER_CRASH1]);
    alSourcef(Src[SND_ASTER_CRASH1], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_ASTER_CRASH1], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_ASTER_CRASH2], AL_BUFFER, Buf[SND_ASTER_CRASH2]);
    alSourcef(Src[SND_ASTER_CRASH2], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_ASTER_CRASH2], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_ASTER_CRASH3], AL_BUFFER, Buf[SND_ASTER_CRASH3]);
    alSourcef(Src[SND_ASTER_CRASH3], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_ASTER_CRASH3], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_UFO_ENGINE], AL_BUFFER, Buf[SND_UFO_ENGINE]);
    alSourcei(Src[SND_UFO_ENGINE], AL_LOOPING, AL_TRUE);
    alSourcef(Src[SND_UFO_ENGINE], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_UFO_ENGINE], AL_MAX_DISTANCE, MaxDist);
    alSourcef(Src[SND_UFO_ENGINE], AL_GAIN, SND_VOL_UFO_ENGINE);

    alSourcei(Src[SND_START_BEEP], AL_BUFFER, Buf[SND_START_BEEP]);
    alSourcef(Src[SND_START_BEEP], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_START_BEEP], AL_MAX_DISTANCE, MaxDist);
    alSourcef(Src[SND_START_BEEP], AL_GAIN, SND_VOL_START_BEEP);

    alSourcei(Src[SND_BONUS_BEEP], AL_BUFFER, Buf[SND_BONUS_BEEP]);
    alSourcef(Src[SND_BONUS_BEEP], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_BONUS_BEEP], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_BROOM], AL_BUFFER, Buf[SND_BROOM]);
    alSourcef(Src[SND_BROOM], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_BROOM], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_POWERUP], AL_BUFFER, Buf[SND_POWERUP]);
    alSourcef(Src[SND_POWERUP], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_POWERUP], AL_MAX_DISTANCE, MaxDist);

    alSourcei(Src[SND_SHIP_FIRE_POWER], AL_BUFFER, Buf[SND_SHIP_FIRE_POWER]);
    alSourcef(Src[SND_SHIP_FIRE_POWER], AL_REFERENCE_DISTANCE, RefDist);
    alSourcef(Src[SND_SHIP_FIRE_POWER], AL_MAX_DISTANCE, MaxDist);
    alSourcef(Src[SND_SHIP_FIRE_POWER], AL_GAIN, SND_VOL_SHIP_FIRE_POWER);

    m_bSamplesLoaded=true;
    if(alGetError()!=AL_NO_ERROR) return false;

    return true;
}

void TGESoundEngineOAL::FreeSound(void)
{
    if(!m_bSamplesLoaded) return;
    alDeleteBuffers(NUM_BUFFERS, &Buf[0]);
    alDeleteSources(NUM_SOURCES, &Src[0]);
    m_bSamplesLoaded=false;
}

void TGESoundEngineOAL::SetVolume(float in_Vol)
{
    m_Volume=in_Vol;
    alListenerf(AL_GAIN, m_Volume);
}

void TGESoundEngineOAL::Mute()
{
    alListenerf(AL_GAIN, 0.0);
}

void TGESoundEngineOAL::Unmute()
{
    alListenerf(AL_GAIN, m_Volume);
}
#endif //USE_OPENAL
/////////////////////////////////////////////////////////////////////////////////////////////

TGEMusicEngineBASS::TGEMusicEngineBASS(void):
    SoundEngine()
{
    m_Channel = 0;
    m_hMus = 0;
}

bool TGEMusicEngineBASS::Open(void)
{
    // Initialize the default output device with 3D support
    BASS_Init(-1,44100,BASS_DEVICE_3D,NULL,NULL);
    return InitSound();
}

void TGEMusicEngineBASS::Close(void)
{
    FreeSound();
    BASS_Free();
}

bool TGEMusicEngineBASS::InitSound(void)
{
    if(m_hMus) return true;

    //m_hMus=BASS_MusicLoad(false, "sound/bwv1052a.it", 0, 0, BASS_SAMPLE_LOOP, 0);
    m_hMus=BASS_StreamCreateFile(false, "sound/BWV1052.ogg", 0, 0, BASS_SAMPLE_LOOP);
    if (m_hMus) BASS_ChannelSetAttribute(m_hMus, BASS_ATTRIB_VOL, 0.4f);
    return true;
}

void TGEMusicEngineBASS::FreeSound(void)
{
    if(!m_hMus) return;

    //BASS_MusicFree(m_hMus);
    BASS_StreamFree(m_hMus);

    m_hMus = 0;
}

void TGEMusicEngineBASS::SetVolume(float in_Vol)
{
    m_Volume=in_Vol;
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, DWORD(m_Volume*10000));
    BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, DWORD(m_Volume*10000));
}

void TGEMusicEngineBASS::Play(BOOL in_bRestart)
{
    if(!m_hMus) return;
//	if(!m_Channel)
        m_Channel=BASS_ChannelPlay(m_hMus, in_bRestart);
}

void TGEMusicEngineBASS::Pause()
{
    if(m_Channel)
        BASS_ChannelPause(m_hMus);
}

void TGEMusicEngineBASS::Stop()
{
    if(m_Channel)
        BASS_ChannelStop(m_hMus);
    m_Channel = 0;
}

void TGEMusicEngineBASS::Mute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, 0);
}

void TGEMusicEngineBASS::Unmute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, DWORD(m_Volume*10000));
}

void TGEMusicEngineBASS::SlideVol(float in_NewVol, DWORD in_Time)
{
    if(BASS_ChannelIsActive(m_Channel)==BASS_ACTIVE_STOPPED) return;
    BASS_ChannelSlideAttribute(m_Channel, BASS_ATTRIB_VOL, in_NewVol, in_Time);
}

bool TGEMusicEngineBASS::IsStarted(void)
{
    DWORD r=BASS_ChannelIsActive(m_hMus);
    return r!=BASS_ACTIVE_STOPPED;
}

/////////////////////////////////////////////////////////////////////////////////////////////
