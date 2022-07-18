#include <assert.h>
#include "ObjectSound.h"
#include "Sound.h"

ObjectSound::ObjectSound(void)
{
    m_SoundID=-1;
    m_Volume=1.0;
}

ObjectSoundBASS::ObjectSoundBASS(void):ObjectSound()
{
    m_Channel = 0;
}

void ObjectSoundBASS::Play(void)
{
    assert(m_SoundID!=-1);
    if(m_SoundID==-1) return;
    m_Channel=BASS_SampleGetChannel(geSound.GetSample(m_SoundID), FALSE);
    assert(m_Channel != 0);
    BASS_ChannelSetAttribute(m_Channel, BASS_ATTRIB_VOL, m_Volume);
    BOOL bRes=BASS_ChannelPlay(m_Channel, FALSE);
    assert(bRes==TRUE);
}

void ObjectSoundBASS::Pause(void)
{
    assert(m_SoundID!=-1);
    if(m_SoundID==-1) return;
    BASS_ChannelPause(m_Channel);
}

void ObjectSoundBASS::Stop(void)
{	
    assert(m_SoundID!=-1);
    if(m_SoundID==-1) return;
    BASS_ChannelStop(m_Channel);
}

void ObjectSoundBASS::SetVolume(float in_Volume)
{
    assert(m_SoundID!=-1);
    m_Volume=in_Volume;
    if(m_SoundID==-1) return;
    if(BASS_ChannelIsActive(m_Channel)==BASS_ACTIVE_STOPPED)
        m_Channel=BASS_SampleGetChannel(geSound.GetSample(m_SoundID), FALSE);
    BASS_ChannelSetAttribute(m_Channel, BASS_ATTRIB_VOL, m_Volume);
}

void ObjectSoundBASS::SlideVol(float in_NewVol, DWORD in_Time)
{
    assert(m_SoundID!=-1);
    if(m_SoundID==-1) return;
    if(BASS_ChannelIsActive(m_Channel)==BASS_ACTIVE_STOPPED) return;
    BASS_ChannelSlideAttribute(m_Channel, BASS_ATTRIB_VOL, in_NewVol, in_Time);
}