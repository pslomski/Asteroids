#include "TempObject.hpp"

TempObject::TempObject() : Object() {}

TempObject::TempObject(Float in_LifeTime) : LifeTime(in_LifeTime) {}

bool TempObject::expired()
{
    return LifeTime.inc(dt);
}

void TempObject::setExpired()
{
    LifeTime.setExpired();
}
