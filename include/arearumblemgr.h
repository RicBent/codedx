#pragma once

#include "sead.h"

class AreaRumbleMgr : public sead::IDisposer
{
public:
    static AreaRumbleMgr* instance;

    void rumble(s32 intensity, s8 unk2, s8 unk3, s8 unk4);
};
