#include "actor/enemy.h"

class BobOmb : public Enemy     // actually inherits CarryableEnemy
{
public:
    void decideFirstStateCustom();
    void checkColliderAddTimer();

    u8 _unk189C[0x18DC-0x189C];
    u16 flags;                  // 18DC
    u8 _unk18DE[0x1928-0x18DE];
    u32 type;                   // 1928
    u8 _unk192C[0x1938-0x192C];
    u32 fuseTimer;              // 1938
    u8 _unk193C[0x1BA0-0x193C];

    DECLARE_STATE(BobOmb, Kicked);

    static const u16 fuseTimes[8];
};

const u16 BobOmb::fuseTimes[8] = { 240, 180, 120, 90, 60, 45, 30, 15 };


void BobOmb::decideFirstStateCustom()
{
    if (type == 7)
    {
        if ((settings2 >> 8) & 0xFF)
            removeActiveColliders();

        flags |= 4; // Mark as ignited, Todo: start red flashing
        fuseTimer = fuseTimes[(settings2 >> 4) & 0xF];
        direction = settings2 & 1;
        doStateChange(&StateID_Kicked);
    }
}

void BobOmb::checkColliderAddTimer()
{
    u32 collisionAddTimer = (settings2 >> 8) & 0xFF;

    if (collisionAddTimer > 0)
    {
        if (--collisionAddTimer == 0)
        {
            addActiveColliders();
            settings2 &= 0xFFFF00FF;
        }
        else
            settings2 = (settings2 & 0xFFFF00FF) | (collisionAddTimer << 8);
    }
}
