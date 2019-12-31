#pragma once

#include "stageactor.h"
#include "collisionmgr.h"
#include "tilecheck.h"

class CollisionActor : public StageActor
{
    SEAD_RTTI_OVERRIDE(CollisionActor, StageActor)

public:
    CollisionActor(const ActorBuildInfo* buildInfo);
    virtual ~CollisionActor();

    void afterCreate(u32) override;
    u32 beforeExecute() override;
    void afterExecute(u32) override;
    u32 onDelete() override;
    void* getCollisionMgr() override;

    virtual void vf84(u8);              // sets _17AA
    virtual u8 vf88();                  // returns _17AA
    virtual void vf8C();                // nullsub
    virtual void vf90();                // nullsub
    virtual u32 vf94();                 // returns 0
    virtual void vf98(f32);             // sets _7C
    virtual u32 vf9C();                 // returns 0
    virtual void vfA0();                // nullsub
    virtual void vfA4();                // nullsub
    virtual u32 vfA8();                 // returns 0
    virtual void vfAC(Vec2*);           // sets x and y position
    virtual void vfB0(f32);             // sets _7C
    virtual u32 vfB4();                 // returns 1
    virtual u32 vfB8();                 // returns 0
    virtual void getRect(Rect* rect);

    void handleGravity();
    void handleSpeed();

    inline bool checkForSuitableGround(f32 xOffset, f32 yOffset)
    {
        TileCheck::Param checkParam = { 0 };
        checkParam._2 = _56;
        checkParam._3 = _57;

        TileCheck tileCheck(checkParam);

        Vec2 a = { position.x, position.y };
        Vec2 b = { position.x + xOffset, position.y + yOffset };

        return tileCheck.check(nullptr, a, b, 8);
    }

    u32 _284;                           // 284
    ActorCollisionMgr collisionMgr;     // 288
    u32 _1770;                          // 1770 Inited to 0
    u32 _1774;                          // 1774 Inited to 0
    Vec3* _1778;                        // 1778 Inited to &position
    u8 _177C;                           // 177C Inited to 0
    u32 _1780;                          // 1780 Inited to 0
    f32 _1784;                          // 1784 Inited to 1.0
    u32 _1788;                          // 1788 Inited to 0
    u32 _178C;                          // 178C Inited to 0
    u32 _1790;                          // 1790 Inited to 0
    u32 _1794;                          // 1794 Inited to 0
    f32 _1798;                          // 1798 Inited to 1.5
    f32 _179C;                          // 179C Inited to -1.5
    f32 _17A0;                          // 17A0 Inited to -0.0625
    u32 _17A4;                          // 17A4 Inited to 0
    u32 _17A8;                          // 17A8 Inited to 0
    u32 _17AC;                          // 17AC Inited to 0
};
