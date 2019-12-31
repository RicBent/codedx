#pragma once

#include "actor/enemy.h"

class BrosBase : public Enemy
{
    SEAD_RTTI_OVERRIDE(BrosBase, Enemy)

public:
    BrosBase(const ActorBuildInfo* buildInfo);
    virtual ~BrosBase();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    void killAtGoal() override;

    void vfC8() override;
    void freeze() override;
    void vfD4() override;
    void vfDC() override;
    void vfE0() override;

    void collisionPlayer(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    void collisionYoshi(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionStar(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionPropellerDrill(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionIceball(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionHammer(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool vf150(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    DECLARE_STATE_OVERRIDE(BrosBase, DieFumi);  // 1BC 1C0 1C4
    DECLARE_STATE_OVERRIDE(BrosBase, DieFall);  // 1C8 1CC 1D0

    DECLARE_STATE_VIRTUAL(BrosBase, Move);      // 270 274 278
    DECLARE_STATE_VIRTUAL(BrosBase, Attack);    // 27C 280 284
    DECLARE_STATE_VIRTUAL(BrosBase, JumpSt);    // 288 28C 290
    DECLARE_STATE_VIRTUAL(BrosBase, Jump);      // 294 298 29C
    DECLARE_STATE_VIRTUAL(BrosBase, JumpEd);    // 2A0 2A4 2A8
    DECLARE_STATE_VIRTUAL(BrosBase, AirAttack); // 2AC 2B0 2B4
    DECLARE_STATE_VIRTUAL(BrosBase, Down);      // 2B8 2BC 2C0

    virtual void vf2C4();
    virtual f32 getProjectileCreateFrame();     // 2C8
    virtual f32 getProjectileThrowFrame();      // 2CC
    virtual void setWalkingSpeed();             // 2D0
    virtual bool vf2D4();
    virtual s32 getTextureId();                 // 2D8
    virtual void setWalkingTimer();             // 2DC
    virtual Vec3 vf2E0();
    virtual void vf2E4();
    virtual void vf2E8();
    virtual void createProjectile();            // 2EC
    virtual void throwProjectile();             // 2F0
    virtual void setHopTimer();                 // 2F4
    virtual void setHopSpeed();                 // 2F8
    virtual void doAirAttack();                 // 2FC
    virtual u32 vf300();
    virtual u32 vf304();
    virtual void doAttack();                    // 308
    virtual void setThrowAnimation();           // 30C
    virtual void vf310();
    virtual void vf314();
    virtual void vf318();
    virtual void vf31C();
    virtual void vf320();
    virtual void vf324();
    virtual void vf328();
    virtual bool vf32C();
    virtual void vf330();
    virtual void vf334();

    u8 _unk189C[0x1990-0x189C];                 // 189C
    u32 walkingTimer;                           // 1990
    u32 hopTimer;                               // 1994
    u8 _1998[0x19CC-0x1998];                    // 1998
    u8 walkingDirection;                        // 19CC
    u8 _unk19CD[0x30B8-0x19CD];                 // 19CD
};