#ifdef USE_OPENAL

#include "SoundEngineOal.hpp"

TGESoundEngineOAL::TGESoundEngineOAL():
    TGESoundEngineBase()
{
    m_bSamplesLoaded=false;
    for(int i=0; i<NUM_BUFFERS; ++i) Buf[i]=0;
    for(int i=0; i<NUM_SOURCES; ++i) Src[i]=0;
}

bool TGESoundEngineOAL::Open()
{
    alutInit(NULL, 0);
    return InitSound();
}

void TGESoundEngineOAL::Close()
{
    FreeSound();
    alutExit();
}

void TGESoundEngineOAL::StopAllSounds()
{
    for(int i=0; i<NUM_SOURCES; ++i) alSourceStop(Src[i]);
}

bool TGESoundEngineOAL::InitSound()
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

void TGESoundEngineOAL::FreeSound()
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
