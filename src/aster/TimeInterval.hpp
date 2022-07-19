#pragma once
#include "Types.h"

class TimeInterval
{
public:
    TimeInterval();
    TimeInterval(Float timeSpan);
    Float get() const
    {
        return interval;
    }
    void set(Float newInterval);
    void reset();
    void reset(Float newInterval);
    void setExpired();
    bool hasExpired() const;
    bool inc(Float dt);
    Float ratio();

    Float interval;
    Float elapsed{0.0};
};
