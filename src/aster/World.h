#pragma once

#include "Types.h"

class World final
{
public:
    World();

    int MusicVol;
    int SoundVol;
    bool IsGameRunning;
    Float dt; // Time step between GetTimeDelta calls.
    Float interp; // movement interpolation coeff.
    int scrWidth;
    int scrHeight;
    // Game area bounds
    Float clipLeft, clipRight;
    Float clipBottom, clipTop;

    Float getWidth()
    {
        return clipRight - clipLeft;
    }
    
    Float getHeight()
    {
        return clipTop - clipBottom;
    }
    
    PointF GetCenter()
    {
        return PointF(
            (clipRight + clipLeft) / 2.0,
            (clipTop + clipBottom) / 2.0
        );
    }
    
    PointF GetRandomPosAtEdge();
    
    DWORD GetTicks()
    {
        return time_;
    }
    
    Float getCurrentTime();
    void readSettings();
    void saveSettings();

private:
    void setTime(DWORD in_Time)
    {
        timePrev_ = time_;
        time_ = in_Time;
    };

    bool usePerfCounter_;
    double frequency_;
    DWORD timePrev_;
    DWORD time_;
};

extern World geWorld;
