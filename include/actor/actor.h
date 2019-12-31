#pragma once

#include "util/vec3.h"
#include "util/vec3i.h"
#include "sead.h"
#include "profile.h"

struct ActorInfo
{
    static const ActorInfo Default;
    
    s32 _0;                 // 0
    s32 _4;                 // 4
    s32 _8;                 // 8
    s32 _C;                 // C
    s32 _10;                // 10
    s32 _14;                // 14
    u16 _18;                // 18
    u16 _1A;                // 1A
    u16 _1C;                // 1C
    u16 _1E;                // 1E
    u32 _20;                // 20
};

struct ActorBuildInfo
{
    u32 settings1;          // 0
    u32 settings2;          // 4
    u32 parentId;           // 8
    Profile* profile;       // C
    Vec3 position;          // 10
    u32 rotation;           // 1C
    u8 _20;                 // 20
    u8 eventId1;            // 21
    u8 eventId2;            // 22
    u8 _23;                 // 23
    u8 movementId;          // 24
    u8 linkId;              // 25
    u8 initStateFlag;       // 26
    u8 _27;                 // 27
    u32 _28;                // 28
};


class Actor
{
    SEAD_RTTI_BASE(Actor)

public:
    Actor(const ActorBuildInfo* buildInfo);
    virtual ~Actor();

    virtual u32 beforeCreate();
    virtual u32 onCreate();
    virtual void afterCreate(u32);

    virtual u32 beforeExecute();
    virtual u32 onExecute();
    virtual void afterExecute(u32);
    virtual void finalExecute();

    virtual u32 beforeDraw();
    virtual u32 onDraw();
    virtual void afterDraw(u32);

    virtual u32 beforeDelete();
    virtual u32 onDelete();
    virtual void afterDelete(u32);

    sead::Heap* heap;       // 4
    u32 id;                 // 8
    Profile* profile;       // C
    u8 _10;                 // 10
    u8 _11;                 // 11
    u8 _12;                 // 12
    bool isDeleted;         // 13
    u32 settings1;          // 14
    u32 settings2;          // 18
    u8 movementId;          // 1C
    u8 linkId;              // 1D
    u8 initStateFlag;       // 1E 
    sead::ListNode _20;     // 20   
    u32 childCount;         // 28
    s32 _2C;                // 2C
    u32 _30;                // 30
    u32 _34;                // 34
    Actor* parent;          // 38
    u32 _3C;                // 3C
    u32 _40;                // 40
    u32 _44;                // 44
    u32 _48;                // 48
    u32 _4C;                // 4C
};
