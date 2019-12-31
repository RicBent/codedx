#pragma once

#include "sead.h"
#include "util/vec2.h"

class StageActor;
class CollisionMgr;

class ColliderBase : public sead::IDisposer     // size: 0x154
{
    SEAD_RTTI_BASE(ColliderBase)

public:
    typedef void (*Callback)(ColliderBase* cSelf, CollisionMgr* otherMgr, u32 unk);

    class List
    {
    public:
        struct Node
        {
            ColliderBase* owner;    // 0
            Node* next;             // 4
            Node* prev;             // 8
        };

    public:
        virtual void insert(Node* where, Node* node);   // 0
        virtual void remove(Node* node);                // 4
        virtual void insertBack(Node* node);            // 8
        virtual void insertFront(Node* node);           // C
        virtual void clear();                           // 10

        Node* first;            // 4
        Node* last;             // 8
    };

    struct Node
    {
        struct Unk
        {
            u32 _0;
            u32 _4;
            f32 _8;
            u32 _C;
        };

        u16 _0;
        Unk _4;
        u32 _14;
        u32 _18;
        u32 _1C;
    };

    enum Types
    {
        TypeSolid               = 0,
        TypeCoin                = 1,
        TypeBlueCoin            = 3,
        TypeWater               = 19,
        TypeLava                = 20,
        TypePoison              = 21,
        TypeQuicksand           = 22
    };

    enum SurfaceTypes
    {
        SurfaceTypeRegular      = 0,
        SurfaceTypeIce          = 1,
        SurfaceTypeSnow         = 2,
        SurfaceTypeQuicksand    = 3,
        SurfaceTypeSand         = 4,
        SurfaceTypeGrass        = 5
    };

public:
    ColliderBase();
    virtual ~ColliderBase();

    virtual bool vf10(u32* unk1, u32 unkMask);
    virtual u32 vf14(u32* unk);
    virtual void vf18() = 0;
    virtual void execute() = 0;
    virtual bool vf20(u32* unk1, u32* unk2, u32* unk3, Vec2* unk4, u32 unk5) = 0;
    virtual bool vf24(u32* unk1, u32* unk2, Vec2* unk3, u32 unk4, u32* unk5) = 0;
    virtual bool vf28(u32* unk1, Vec2* unk2) = 0;
    virtual bool vf2C(u32* unk1) = 0;
    virtual void vf30();
    virtual void vf34() = 0;
    virtual void vf38(u32* unk1) = 0;
    virtual bool vf3C(Vec2* unk1) = 0;

    void setType(u32 type);
    void setSolidity(u32 solidity);
    void setSurfaceType(u32 surfaceType);

    List::Node listNodes[8];    // 10 
    Rect rect;                  // 70
    u8 _unk80[0x90-0x80];       // 80
    StageActor* owner;          // 90
    u32 _unk94;                 // 94
    Vec3* ownerPosition;        // 98
    Vec3* owner248;             // 9C
    u8* owner56;                // A0
    u8* owner57;                // A4
    u8* ownerPlayerId;          // A8
    Vec2 distToCenter;          // AC
    u8 _unkB4[0xF4-0xB4];       // B4
    u32 rotation;               // F4
    u8 _unkF8[0x138-0xF8];      // F8
    Callback _138;              // 138
    Callback _13C;              // 13C
    Callback _140;              // 140
    u8 _unk144[0x154-0x144];    // 144
};


class ShapedCollider : public ColliderBase  // size: 0x16C
{
    SEAD_RTTI_OVERRIDE(ShapedCollider, ColliderBase)

public:
    struct Info
    {
        Vec2 distToCenter;  // 0
        f32 _8;             // 8
        f32 _C;             // C
        Vec2 topLeft;       // 10
        Vec2 bottomRight;   // 18
        u32 rotation;       // 20

    };

public:
    ShapedCollider();
    virtual ~ShapedCollider();

    void init(StageActor* owner, const Info& info);

    bool vf10(u32* unk1, u32 unkMask) override;
    u32 vf14(u32* unk) override;
    void vf18() override;
    void execute() override;
    bool vf20(u32* unk1, u32* unk2, u32* unk3, Vec2* unk4, u32 unk5) override;
    bool vf24(u32* unk1, u32* unk2, Vec2* unk3, u32 unk4, u32* unk5) override;
    bool vf28(u32* unk1, Vec2* unk2) override;
    bool vf2C(u32* unk1) override;
    void vf30() override;
    void vf34() override;
    void vf38(u32* unk1) override;
    bool vf3C(Vec2* unk1) override;

    virtual void vf40();


    u8 _unk154[0x16C-0x154];
};


class RectCollider : public ShapedCollider  // size: 0x290
{
    SEAD_RTTI_OVERRIDE(RectCollider, ColliderBase)

public:
    RectCollider();

    bool vf28(u32* unk1, Vec2* unk2) override;


    u8 _unk16C[0x190-0x16C];    // 16C
    Node nodes[8];              // 190
};


class SolidOnTopCollider : public ColliderBase  // size: 0x170
{
    SEAD_RTTI_OVERRIDE(SolidOnTopCollider, ColliderBase)

public:
    struct Info
    {
        Vec2 distToCenter;  // 0
        f32 _8;             // 8
        f32 _C;             // C
        Vec2* points;       // 10
        u32 rotation;       // 14
    };

public:
    SolidOnTopCollider();
    virtual ~SolidOnTopCollider();

    void init(StageActor* owner, const Info& info, u32 numPoints, sead::Heap* heap = nullptr);

    void vf18() override;
    void execute() override;
    bool vf20(u32* unk1, u32* unk2, u32* unk3, Vec2* unk4, u32 unk5) override;
    bool vf24(u32* unk1, u32* unk2, Vec2* unk3, u32 unk4, u32* unk5) override;
    bool vf28(u32* unk1, Vec2* unk2) override;
    bool vf2C(u32* unk1) override;
    void vf30() override;
    void vf34() override;
    void vf38(u32* unk1) override;
    bool vf3C(Vec2* unk1) override;

    u32 numPoints;          // 154
    u8 _158[0x16C-0x158];
    f32 _16C;
};


class CircularCollider : public ColliderBase    // size: 0x190
{
    SEAD_RTTI_OVERRIDE(CircularCollider, ColliderBase)

public:
    struct Info
    {
        Vec2 distToCenter;  // 0
        f32 _8;             // 8
        f32 _C;             // C
        f32 _10;            // 10
        f32 _14;            // 14
        f32 radius;         // 18
        u32 rotation;       // 1C
    };

public:
    CircularCollider();

    void init(StageActor* owner, const Info& info);

    bool vf10(u32* unk1, u32 unkMask) override;
    u32 vf14(u32* unk) override;
    void vf18() override;
    void execute() override;
    bool vf20(u32* unk1, u32* unk2, u32* unk3, Vec2* unk4, u32 unk5) override;
    bool vf24(u32* unk1, u32* unk2, Vec2* unk3, u32 unk4, u32* unk5) override;
    bool vf28(u32* unk1, Vec2* unk2) override;
    bool vf2C(u32* unk1) override;
    void vf30() override;
    void vf34() override;
    void vf38(u32* unk1) override;
    bool vf3C(Vec2* unk1) override;

    u8 _154[0x190-0x154];
};



class ColliderMgr : public sead::IDisposer    // size: 0x64
{
public:
    void add(ColliderBase* collider);

    static ColliderMgr* instance;

    ColliderBase::List lists[7];    // 10
};
