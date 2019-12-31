/*
    TODO:
        - Rotation
*/

#include "actor/stageactor.h"

#include "model.h"
#include "drawmgr.h"
#include "collider.h"
#include "movementhandler.h"
#include "level.h"
#include "tile.h"

class MagicLift : public StageActor
{
public:
    MagicLift(const ActorBuildInfo* buildInfo);
    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    u16* tileData;
    u32 tileW, tileH;

    MovementHandler movementHandler;

    u8 collisionType;
    RectCollider rectCollider;
    SolidOnTopCollider solidOnTopCollider;
};


const Profile magicLiftProfile(&MagicLift::build, ProfileId::MagicLift, "MagicLift", nullptr, 0);


MagicLift::MagicLift(const ActorBuildInfo* buildInfo) : StageActor(buildInfo), tileData(nullptr) { }

Actor* MagicLift::build(const ActorBuildInfo* buildInfo)
{
    return new MagicLift(buildInfo);
}


u32 MagicLift::onCreate()
{
    Level::Area* area = Level::instance->getArea(LevelInfo::instance->area);
    Level::Area::Location* location = area->getLocation(nullptr, settings1 & 0xFF);

    if (!location)
        return 2;

    u32 locX = location->x & ~0xF;
    u32 locY = location->y & ~0xF;
    tileW = (location->w + (location->x & 0xF) + 0xF) / 16;
    tileH = (location->h + (location->y & 0xF) + 0xF) / 16;

    if (!tileW || !tileH)
        return 2;

    tileData = new u16[tileW*tileH];

    for (u32 y = 0; y < tileH; y++)
    {
        for (u32 x = 0; x < tileW; x++)
        {
            u16* tilePtr = TileMgr::getTilePtrCurrentArea(locX + x*16, locY + y*16, 0);
            tileData[x + y*tileW] = tilePtr ? *tilePtr : 0;
        }
    }

    collisionType = (settings1 >> 8) & 0xF;

    if (collisionType == 0)
    {
        ShapedCollider::Info info = { {0.0f, 0.0f}, 0.0f, 0.0f, {tileW * -8.0f, tileH * 8.0f}, {tileW * 8.0f, tileH * -8.0f}, 0 };
        rectCollider.init(this, info);
        rectCollider.setType((settings1 >> 16) & 0xFF);
        rectCollider.setSurfaceType((settings1 >> 12) & 0xF);
        ColliderMgr::instance->add(&rectCollider);
    }
    else if (collisionType == 1)
    {
        Vec2 points[2] = { {tileW * -8.0f, tileH * 8.0f}, {tileW * 8.0f, tileH * 8.0f} };
        SolidOnTopCollider::Info info = { {0.0f, 0.0f}, 0.0f, 0.0f, points, 0 };
        solidOnTopCollider.init(this, info, 2);
        solidOnTopCollider.setType((settings1 >> 16) & 0xFF);
        solidOnTopCollider.setSurfaceType((settings1 >> 12) & 0xF);
        ColliderMgr::instance->add(&solidOnTopCollider);
    }

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    return 1;
}

u32 MagicLift::onExecute()
{
    movementHandler.execute();
    position = movementHandler.position;

    if (collisionType == 0)
        rectCollider.execute();
    else if (collisionType == 1)
        solidOnTopCollider.execute();

    return 1;
}

u32 MagicLift::onDraw()
{
    for (u32 y = 0; y < tileH; y++)
    {
        for (u32 x = 0; x < tileW; x++)
        {
            Vec3 drawPos(position.x + x*16 - tileW*8 + 8, position.y - y*16 + tileH*8 - 8, position.z);
            DrawMgr::instance->drawTile(tileData[y*tileW + x], drawPos, rotation.z, scale);
        }
    }

    return 1;
}

u32 MagicLift::onDelete()
{
    if (tileData)
        delete[] tileData;

    return 1;
}
