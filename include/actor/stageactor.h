#pragma once

#include "actor.h"
#include "activecollider.h"

class StageActor : public Actor
{
    SEAD_RTTI_OVERRIDE(StageActor, Actor)

public:
    StageActor(const ActorBuildInfo* buildInfo);
    virtual ~StageActor();

    void afterCreate(u32) override;
    u32 beforeExecute() override;
    void afterExecute(u32) override;
    u32 beforeDraw() override;

    virtual void setPlayerId(s8);
    virtual void removeActiveColliders();
    virtual void addActiveColliders();
    virtual void* getCollisionMgr();
    virtual void vf54();
    virtual u32 vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void killAtGoal();
    virtual void splashWater(Vec3*);
    virtual void splashLava(Vec3*);
    virtual void splashLavaWave(Vec3*);
    virtual void splashPoison(Vec3*);
    virtual bool isOffScreen();
    virtual void damageFromUnder();

    s8 distanceToPlayer(const Vec2& out);
    u8 directionToPlayerH(const Vec3& position);
    u8 directionToPlayerV(const Vec3& position);
    void cullCheck(u32 unkMask = 0);

    u32 direction;              // 50   Inited to 0
    s8 playerId;                // 54   Inited to -1
    s8 _55;                     // 55   Inited to -1
    u8 _56;                     // 56   Inited to buildInfo->_20
    u8 _57;                     // 57   Inited to 1
    u32 _58;                    // 58   Inited to 0
    u32 _5C;                    // 5C   Inited to 0
    u32 _60;                    // 60   Inited to 0
    u32 _64;                    // 64   Inited to 0
    u32 _68;                    // 68   Inited to 0, related to x speed
    Vec3 position;              // 6C
    Vec3 speed;                 // 78
    Vec3 maxSpeed;              // 84   Inited to 0
    Vec3 scale;                 // 90   Inited to 1.0
    Vec3i rotation;             // 9C   Inited to 0
    u32 _A8;                    // A8   Inited to 0
    u32 _AC;                    // AC   Inited to 0
    u32 _B0;                    // B0   Inited to 0
    u32 _B4;                    // B4   Inited to 0
    u32 _B8;                    // B8   Inited to 0
    ActiveCollider aCollider;   // BC
    f32 _1EC;                   // 1EC
    f32 _1F0;                   // 1F0
    f32 _1F4;                   // 1F4
    f32 _1F8;                   // 1F8
    f32 _1FC;                   // 1FC
    f32 _200;                   // 200
    f32 _204;                   // 204
    f32 _208;                   // 208
    f32 _20C;                   // 20C
    f32 _210;                   // 210
    u8 zoneId;                  // 214
    u8 type;                    // 215  0: StageActor, 1: Player, 2: Yoshi, 3: Enemy, 4: Unknown
    u8 _216;                    // 216  Inited to 1
    u8 _217;                    // 217  Inited to 1
    u8 _218;                    // 218  Inited to 0
    u8 _219;                    // 219  Inited to 1
    u8 _21A;                    // 21A  Inited to 0
    u8 eventId1;                // 21B
    u8 eventId2;                // 21C
    u16 _21E;                   // 21E  Inited to actorInfo->_20
    u32 _220;                   // 220  Inited to 0
    u32 _224;                   // 224  Inited to 0
    u32 _228;                   // 228  Inited to 0
    u32 _22C;                   // 22C  Inited to 0
    u32 _230;                   // 230  Inited to 0
    u32 _234;                   // 234  Inited to 0
    u32 _238;                   // 238  Inited to profile->flags
    Vec3 effectOffset;          // 23C  Inited to 0
    Vec3 _248;                  // 248  Inited to position
    Vec3 _254;                  // 254  Inited to position
    Vec3 _260;                  // 260  Inited to position
    u32 _26C;                   // 26C  Inited to o
    u32 _270;                   // 270  Inited to o
    u32 _274;                   // 274  Inited to o
    u32 _278;                   // 278  Inited to buildInfo->_28
    u32 _27C;                   // 27C  Inited to o
    u32 _280;                   // 280  Inited to o
};
