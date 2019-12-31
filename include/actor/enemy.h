#pragma once

#include "multistateactor.h"
#include "enemyfreezemgr.h"

class Enemy : public MultiStateActor
{
    SEAD_RTTI_OVERRIDE(Enemy, MultiStateActor)

public:
    Enemy(const ActorBuildInfo* buildInfo);
    virtual ~Enemy();

    u32 beforeExecute() override;
    void damageFromUnder() override;
    void vfA4() override;
    u32 vfA8() override;
    void doStateChange(StateBase* state) override;

    // TODO
    virtual void vfC4();
    virtual void vfC8();
    virtual bool vfCC();
    virtual void freeze();                                                                      // creates ice actors
    virtual void vfD4();                                                                        // called on freeze
    virtual void vfD8();                                                                        // called on freeze break
    virtual void vfDC();                                                                        // called on freeze break, decides next state
    virtual void vfE0();
    virtual void vfE4();

    virtual bool vfE8(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision enemy 2
    virtual bool vfEC(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision player
    virtual bool vfF0(bool& unk, ActiveCollider* acSelf, ActiveCollider* acOther);              // pre collision enemy
    virtual void vfF4(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision yoshi related
    virtual bool vfF8(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision yoshi
    virtual bool vfFC(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision unk
    virtual bool vf100(ActiveCollider* acSelf, ActiveCollider* acOther);                        // pre collision stage actor

    virtual void collisionEnemy(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void collisionPlayer(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void collisionYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void vf110(ActiveCollider* acSelf, ActiveCollider* acOther);

    virtual bool collisionStar(ActiveCollider* acSelf, ActiveCollider* acOther);                // 3
    virtual bool collisionSlide(ActiveCollider* acSelf, ActiveCollider* acOther);               // 5
    virtual bool collisionPropellerDrill(ActiveCollider* acSelf, ActiveCollider* acOther);      // 13
    virtual bool vf120(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 8
    virtual bool collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther);         // 7
    virtual bool collisionGroundPoundYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);    // 7
    virtual bool collisionPenguinSlide(ActiveCollider* acSelf, ActiveCollider* acOther);        // 10
    virtual bool collisionPipeCannon(ActiveCollider* acSelf, ActiveCollider* acOther);          // 17
    virtual bool vf134(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 25
    virtual bool collisionThrowableObject(ActiveCollider* acSelf, ActiveCollider* acOther);     // 9
    virtual bool collisionFireball(ActiveCollider* acSelf, ActiveCollider* acOther);            // 1 14
    virtual bool collisionIceball(ActiveCollider* acSelf, ActiveCollider* acOther);             // 2 21
    virtual bool collisionHammer(ActiveCollider* acSelf, ActiveCollider* acOther);              // 19
    virtual bool collisionFireballYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);       // 20
    virtual bool vf14C(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 24
    virtual bool vf150(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 26
    virtual bool vf154(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 3
    virtual bool vf158(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 27

    virtual void vf15C();
    virtual void vf160();
    virtual void vf164();
    virtual bool isOnGround();
    virtual void vf16C();
    virtual void vf170();
    virtual void vf174();
    virtual void vf178();
    virtual void vf17C();
    virtual void vf180();
    virtual void vf184();
    virtual void vf188();
    virtual void vf18C();
    virtual void vf190();
    virtual void vf194();
    virtual void vf198();
    virtual void vf19C();
    virtual void vf1A0();
    virtual void vf1A4();
    virtual void vf1A8();
    virtual void vf1AC();
    virtual void vf1B0();
    virtual void vf1B4();
    virtual void vf1B8();
    
    DECLARE_STATE_VIRTUAL(Enemy, DieFumi);  // 1BC 1C0 1C4
    DECLARE_STATE_VIRTUAL(Enemy, DieFall);  // 1C8 1CC 1D0

    virtual void vf1D4();
    virtual void vf1D8();
    virtual void vf1DC();
    virtual void vf1E0();
    virtual void vf1E4();
    virtual void vf1E8();
    virtual void vf1EC();
    virtual void vf1F0();
    virtual void vf1F4();
    virtual void vf1F8();
    virtual void vf1FC();
    virtual void vf200();
    virtual void vf204();
    virtual void vf208();
    virtual void vf20C();
    virtual void vf210();
    virtual void vf214();
    virtual void vf218();
    virtual void vf21C();
    virtual void vf220();
    virtual void vf224();
    virtual void vf228();
    virtual void vf22C();
    virtual void vf230();
    virtual void vf234();
    virtual void vf238();
    virtual void vf23C();
    virtual void vf240();
    virtual void vf244();
    virtual void vf248();
    virtual void vf24C();
    virtual void vf250();
    virtual void vf254();
    virtual void vf258();
    virtual void vf25C();
    virtual void vf260();

    DECLARE_STATE_VIRTUAL(Enemy, Ice);  // 264 268 26C 

    static void collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther);
    u32 processCollision(ActiveCollider* acSelf, ActiveCollider* acOther, u32 unk);
    void killPlayerJump(StageActor* player, const Vec2& speed, StateBase* state);
    void killPlayerSpin(StageActor* player);
    void killYoshiStomp(StageActor* player);

    f32 _17D8;                  // 17D8 Inited to 1.5
    f32 _17DC;                  // 17DC Inited to 3.9
    f32 _17E0;                  // 17E0 Inited to -4.0
    f32 _17E4;                  // 17E4 Inited to ~ -0.25
    u32 _17E8;                  // 17E8 Inited to 0
    u32 _17EC;                  // 17EC Inited to 255
    u32 _17F0;                  // 17F0 Inited to 0
    u32 _17F4;                  // 17F4 Inited to 255
    u8 _17F8;                   // 17F8 Inited to 0
    u8 _unk17F9[3];
    u16 _17FC;                  // 17FC Inited to 0
    u16 _17FE;                  // 17FE Inited to 0
    u16 _1800;                  // 1800 Inited to 0
    u16 _1802;                  // 1802 Inited to 0
    u32 _1804;                  // 1804 Inited to 0
    EnemyFreezeMgr freezeMgr;   // 1808
    u8 _1858[0x20];             // 1858 Class
    Enemy* _1878;               // 1878 Inited to this
    void* _187C;                // 187C Inited to 0x00BE2BE4
    u32 _1880;                  // 1880 Inited to 0
    u32 _1884;                  // 1884 Inited to 0
    u32 _1888;                  // 1888 Inited to 0
    u32 _188C;                  // 188C Inited to 0
    u32 _1890;                  // 1890 Inited to 0
    u32 _1894;                  // 1894 Class
    u8 _1898;                   // 1898 Inited to 0
    u8 _1899;                   // 1899 Inited to 0
    u8 _189A;                   // 189A Inited to 8
};
