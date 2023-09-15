#pragma once

#ifdef USE_OPENAL

#include <al/al.h>

class TGESoundEngineOAL : public TGESoundEngineBase
{
private:
    bool m_bSamplesLoaded;
    // Buffers hold sound data.
    ALuint Buf[NUM_BUFFERS];
    // Sources are points of emitting sound.
    ALuint Src[NUM_SOURCES];

protected:
    bool InitSound();
    void FreeSound();

public:
    TGESoundEngineOAL();
    bool Open();
    void Close();

    void StopAllSounds();
    void SetVolume(float in_Vol);
    void Mute();
    void Unmute();
    ALuint GetSource(int ID) { return Src[ID]; }
};

#endif // USE_OPENAL