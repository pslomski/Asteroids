#pragma once
#include "Types.h"

class TimeInterval
{
public:
    TimeInterval(Float interval_);
    TimeInterval();
    void set(Float newInterval);
    void reset();
    void reset(Float newInterval);
    void setExpired();
    bool inc(Float dt);
    Float ratio();

    Float interval;
    Float elapsed{0.0};
private:
};
