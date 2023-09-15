#pragma once

#include "sound/SoundEngine.hpp"

#include <bass.h>

class MusicEngineBass : public SoundEngine
{
private:
    HSTREAM m_hMus;
    HCHANNEL m_Channel;

protected:
    bool InitSound();
    void FreeSound();

public:
    MusicEngineBass();
    bool Open();
    void Close();
    void SetVolume(float in_Vol);
    void Mute();
    void Unmute();
    void Play(BOOL in_bRestart = false);
    void Pause();
    void Stop();
    void SlideVol(float in_NewVol, DWORD in_Time);
    bool IsStarted();
};
