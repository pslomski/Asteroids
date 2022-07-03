#include "TempObject.hpp"

TempObject::TempObject()
    :Object()
{
}

TempObject::TempObject(Float in_LifeTime) :
    LifeTime(in_LifeTime)
{
}

bool TempObject::Expired()
{
    return LifeTime.inc(dt);
}

void TempObject::SetExpired()
{
    LifeTime.setExpired();
}
