#include "MusicEngineBass.hpp"

MusicEngineBass::MusicEngineBass():
    SoundEngine()
{
    m_Channel = 0;
    m_hMus = 0;
}

bool MusicEngineBass::Open()
{
    // Initialize the default output device with 3D support
    BASS_Init(-1,44100,BASS_DEVICE_3D,nullptr,nullptr);
    return InitSound();
}

void MusicEngineBass::Close()
{
    FreeSound();
    BASS_Free();
}

bool MusicEngineBass::InitSound()
{
    if(m_hMus)
    {
        return true;
    }
    m_hMus=BASS_StreamCreateFile(false, "sound/BWV1052.ogg", 0, 0, BASS_SAMPLE_LOOP);
    if (m_hMus) BASS_ChannelSetAttribute(m_hMus, BASS_ATTRIB_VOL, 0.4f);
    return true;
}

void MusicEngineBass::FreeSound()
{
    if(!m_hMus) return;
    BASS_StreamFree(m_hMus);
    m_hMus = 0;
}

void MusicEngineBass::SetVolume(float in_Vol)
{
    m_Volume=in_Vol;
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, DWORD(m_Volume*10000));
    BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, DWORD(m_Volume*10000));
}

void MusicEngineBass::Play(BOOL in_bRestart)
{
    if(!m_hMus) return;
    m_Channel=BASS_ChannelPlay(m_hMus, in_bRestart);
}

void MusicEngineBass::Pause()
{
    if(m_Channel)
    {
        BASS_ChannelPause(m_hMus);
    }
}

void MusicEngineBass::Stop()
{
    if(m_Channel)
    {
        BASS_ChannelStop(m_hMus);
    }
    m_Channel = 0;
}

void MusicEngineBass::Mute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, 0);
}

void MusicEngineBass::Unmute()
{
    BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, DWORD(m_Volume*10000));
}

void MusicEngineBass::SlideVol(float in_NewVol, DWORD in_Time)
{
    if(BASS_ChannelIsActive(m_Channel)==BASS_ACTIVE_STOPPED) return;
    BASS_ChannelSlideAttribute(m_Channel, BASS_ATTRIB_VOL, in_NewVol, in_Time);
}

bool MusicEngineBass::IsStarted()
{
    DWORD r = BASS_ChannelIsActive(m_hMus);
    return r != BASS_ACTIVE_STOPPED;
}
