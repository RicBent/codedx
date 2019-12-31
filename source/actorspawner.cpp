#include "actor/stageactor.h"
#include "actormgr.h"
#include "eventmgr.h"

#include "model.h"
#include "drawmgr.h"

class ActorSpawner : public StageActor
{
public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 spawnProfileId;
    bool spawned;
};

const Profile actorSpawnerProfile(&ActorSpawner::build, ProfileId::ActorSpawner, "ActorSpawner", nullptr, 0);


ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo) : StageActor(buildInfo) { }

Actor* ActorSpawner::build(const ActorBuildInfo* buildInfo)
{
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate()
{
    if (!eventId2)
        return 2;

    u16 inputId = linkId | ((movementId & 0xF) << 8);
    if (movementId & 0x10)
        spawnProfileId = Profile::spriteToProfileList[inputId];
    else
        spawnProfileId = inputId;

    spawned = false;

    return 1;
}

u32 ActorSpawner::onExecute()
{
    if (EventMgr::instance->isActive(eventId2-1))
    {
        if (!spawned)
        {
            ActorBuildInfo buildInfo = { 0 };
            buildInfo.settings1 = settings1;
            buildInfo.settings2 = settings2;
            buildInfo.profile = Profile::get(spawnProfileId);
            buildInfo.position = position;
            buildInfo.eventId1 = eventId1 & 0xF;
            buildInfo.eventId2 = (eventId1 >> 8) & 0xF;
            ActorMgr::instance->create(&buildInfo, 0);

            spawned = true;
        }
    }
    else
        spawned = false;

    return 1;
}
