#pragma once

#include "types.h"

namespace sead {

class Heap;

class IDisposer
{
public:
    IDisposer();
    virtual ~IDisposer();

private:
    Heap* containingHeap;
    u32 _8;
    u32 _C;
};

}
