#include "TimeInterval.hpp"

TimeInterval::TimeInterval() :
    interval(1.0)
{}

TimeInterval::TimeInterval(Float interval_) :
    interval(interval_)
{}

void TimeInterval::set(Float newInterval)
{
    interval = newInterval;
}

void TimeInterval::reset()
{
    elapsed = 0.0;
}

void TimeInterval::reset(Float newInterval)
{
    elapsed = 0.0;
    interval = newInterval;
}

void TimeInterval::setExpired()
{
    elapsed = interval + 0.01;
}

bool TimeInterval::hasExpired() const
{
    return elapsed >= interval;
}

bool TimeInterval::inc(Float dt)
{
    // true if exceeded given interval
    elapsed += dt;
    return elapsed >= interval;
}

Float TimeInterval::ratio()
{
    return elapsed / interval;
}
