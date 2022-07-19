#pragma once

#include "Types.h"

class World 
{
public:
    World();
    virtual ~World(void);

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
    Float GetHeight()
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
    Float GetCurrentTime();
    void readSettings();
    void saveSettings();

private:
    void SetTime(DWORD in_Time)
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