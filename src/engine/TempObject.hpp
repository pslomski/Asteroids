#pragma once
#include "Object.h"

class TempObject: public Object
{
public:
    TempObject();
    TempObject(Float in_LifeTime);
    ~TempObject() {}
    bool Expired();
    void SetExpired();

    TimeInterval LifeTime;
};
