#pragma once

#include "sound/ObjectSound.hpp"

#include <bass.h>

namespace sound
{
class ObjectSoundBASS : public ObjectSound
{
public:
    ObjectSoundBASS();
    void Play();
    void Pause();
    void Stop();
    void SetVolume(float in_Volume);
    void SetPitch(float in_Pitch) {}
    void SlideVol(float in_NewVol, DWORD in_Time);

private:
    HCHANNEL m_Channel;
};
} // namespace sound
