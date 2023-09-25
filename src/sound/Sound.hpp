#pragma once

#include "bass/MusicEngineBass.hpp"
#include "bass/SoundEngineBass.hpp"
#include "bass/SoundObjectBass.hpp"

namespace sound
{

extern MusicEngineBass geMusic;
extern SoundEngineBass geSound;
} // namespace sound

using TGEObjectSound = sound::ObjectSoundBASS;