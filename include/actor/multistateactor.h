#pragma once

#include "collisionactor.h"
#include "states.h"

class MultiStateActor : public CollisionActor
{
    SEAD_RTTI_OVERRIDE(MultiStateActor, CollisionActor)

public:
    MultiStateActor(const ActorBuildInfo* buildInfo);
    virtual ~MultiStateActor();

    virtual void doStateChange(StateBase* state);

    StateWrapper<MultiStateActor> states;       // 17B0
    u32 _17D4;                                  // 17D4 Probably belongs to StateWrapper or a dereived class of that
};
