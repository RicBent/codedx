#pragma once

#include "sead.h"


class Actor;
class ActorBuildInfo;

class ActorMgr : public sead::IDisposer
{
public:
    static ActorMgr* instance;

    Actor* create(ActorBuildInfo* buildInfo, u32 unk);
};
