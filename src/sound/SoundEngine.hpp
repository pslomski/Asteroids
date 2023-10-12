#pragma once

namespace sound
{
class SoundEngine
{
public:
    SoundEngine()
    {
        m_Volume = 1.0;
        m_bPause = false;
    }
    virtual ~SoundEngine() { Close(); }
    virtual bool Open() = 0;
    virtual void Close() {}
    virtual void SetVolume(float in_Vol) { m_Volume = in_Vol; } // ustawia glosnosc dzwiekow w skali 0-1.
    virtual float GetVolume() { return m_Volume; } // gloscnosc dzwiekow w skali 0-1. 0 oznacza wylaczona
    virtual void Mute() = 0;
    virtual void Unmute() = 0;

protected:
    bool m_bPause;
    float m_Volume;
    virtual bool InitSound() = 0;
    virtual void FreeSound() = 0;
};
} // namespace sound
