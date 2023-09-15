#pragma once

class ObjectSound
{
public:
    ObjectSound();
    void Init(int in_ID, float in_Volume) {
        m_SoundID = in_ID;
        m_Volume = in_Volume;
    }
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual void SetVolume(float in_Volume) = 0;
    virtual void SetPitch(float in_Pitch) = 0;
protected:
    int m_SoundID;
    float m_Volume;
};
