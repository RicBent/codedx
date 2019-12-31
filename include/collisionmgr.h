#pragma once

#include "actor/stageactor.h"


class CollisionMgr
{
    SEAD_RTTI_BASE(CollisionMgr)

public:
    struct Sensor
    {
        f32 _0;
        f32 _4;
        f32 _8;
    };

    enum Flags
    {
        FlagOnGround        = 1 << 0,
        FlagOnSlope         = 1 << 1,
        FlagOnSemiSold      = 1 << 4,
        FlagCollidedRight   = 1 << 18,
        FlagCollidedLeft    = 1 << 19
    };

public:
    CollisionMgr();
    virtual ~CollisionMgr();

    virtual void process();
    virtual void vf14();
    virtual void vf18();
    virtual u32 vf1C() = 0;
    virtual u32 vf20() = 0;
    virtual u32 vf24() = 0;
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();

    void init(StageActor* owner, const Sensor* belowSensor, const Sensor* aboveSensor, const Sensor* adjacentSensor);
    void setSensor(const Sensor* sensor, u32 sensorId);

    inline bool isOnGround()      { return output & FlagOnGround; }
    inline bool isCollidedRight() { return output & FlagCollidedRight; }
    inline bool isCollidedLeft()  { return output & FlagCollidedLeft; }

    inline bool isCollided(u32 direction)
    {
        if (direction > 1) return false;
        return output & (FlagCollidedRight << direction);
    }



    u8 _unk4[0x894-0x4];        // 4

    StageActor* owner;          // 894
    u32 _898;                   // 898
    Vec3* position;             // 89C  &owner->position
    Vec3* _9A0;                 // 8A0  &owner->_248, lastPosition?
    u8* _9A4;                   // 9A4  &owner->_56
    u8* _9A8;                   // 9A8  &owner->_57
    s8* playerId;               // 8AC  &owner->playerId
    u32 output;                 // 8B0

    u8 _unk8B4[0x934-0x8B4];    // 8B4

    Sensor rightSensor;         // 934
    Sensor leftSensor;          // 940
    Sensor aboveSensor;         // 94C
    Sensor belowSensor;         // 958

    u8 _unk964[0x14E8-0x964];   // 964
};


class ActorCollisionMgr : public CollisionMgr
{
    SEAD_RTTI_OVERRIDE(ActorCollisionMgr, CollisionMgr)

public:
    ActorCollisionMgr();

    u32 vf1C() override;
    u32 vf20() override;
    u32 vf24() override;
};