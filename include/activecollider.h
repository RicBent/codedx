#pragma once

#include "sead.h"

class StageActor;

class ActiveCollider : public sead::IDisposer   // size: 0x130
{
public:
    typedef void (*Callback)(ActiveCollider* acSelf, ActiveCollider* acOther);

    enum Shape
    {
        ShapeRectangle      = 0,
        ShapeCircle         = 1,
        ShapeTrapezoidVert  = 2,
        ShapeTrapezoidHoriz = 3
    };

    struct Info
    {
        Vec2 distToCenter;  // 0
        Vec2 distToEdge;    // 8
        u32 shape;          // 10
        u32 _14;            // 14
        u32 _18;            // 18
        u32 _1C;            // 1C
        u32 _20;            // 20
        u32 _24;            // 24
        Callback callback;  // 28
    };

    class List
    {
    public:
        struct Node
        {
            ActiveCollider* owner;  // 0
            Node* next;             // 4
            Node* prev;             // 8
        };

    public:
        virtual void insert(Node* where, Node* node);   // 0
        virtual void remove(Node* node);                // 4
        virtual void insertBack(Node* node);            // 8
        virtual void insertFront(Node* node);           // C
        virtual void clear();                           // 10

        Node* first;                // 4
        Node* last;                 // 8
    };

public:
    ActiveCollider();
    virtual ~ActiveCollider();

    void init(StageActor* owner, const Info*, u32 unk);

    f32 getTop();
    f32 getBottom();
    f32 getLeft();
    f32 getRight();
    f32 getCenterX();
    f32 getCenterY();

    List::Node activeNode;  // 10
    List::Node createNode;  // 1C
    List::Node list3Node;   // 28
    List::Node list4Node;   // 34
    StageActor* owner;      // 40
    u32 _44;
    u32 _48;
    u32 _4C;
    u32 _50;
    u32 _54;
    u32 _58;
    u32 _5C;
    u32 _60;
    u32 _64;
    u32 _68;
    u8 _6C;
    u8 _6D;
    u8 _6E;
    u32 _70;
    Info info;                      // 74
    f32 trapezoidTopLeft;           // A0
    f32 trapezoidTopRight;          // A4
    f32 trapezoidBottomLeft;        // A8
    f32 trapezoidBottomRight;       // AC
    u8 _unkB0[0x130-0xB0];
};


class ActiveColliderMgr : public sead::IDisposer    // size: 0x40
{
public:
    bool isInActiveList(ActiveCollider* aCollider);
    void removeFromActiveList(ActiveCollider* aCollider);

    bool isInCreateList(ActiveCollider* aCollider);
    void addToCreateList(ActiveCollider* aCollider);
    void removeFromCreateList(ActiveCollider* aCollider);

    void removeFromList3(ActiveCollider* aCollider);

    inline void add(ActiveCollider* aCollider)
    {
        if (!isInActiveList(aCollider) && !isInCreateList(aCollider))
            addToCreateList(aCollider);
    }

    inline void remove(ActiveCollider* aCollider)
    {
        removeFromActiveList(aCollider);
        removeFromCreateList(aCollider);
        removeFromList3(aCollider);
    }

    static ActiveColliderMgr* instance;

    ActiveCollider::List activeList;    // 10
    ActiveCollider::List createList;    // 1C
    ActiveCollider::List list3;         // 28
    ActiveCollider::List list4;         // 34
};
