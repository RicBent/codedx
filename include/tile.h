#pragma once

#include "types.h"
#include "level.h"


class TileLayer
{
public:
    u16* getTilePtr(u32 x, u32 y, u32* blockIndexOut = nullptr);
};


class TilesetMgr
{
public:
    TileLayer* getTileLayer(u32 area, u8 layer);

    static TilesetMgr* instance;
};


class TileMgr
{
public:
    static TileMgr* instance;

    static inline u16* getTilePtr(u16 x, u16 y, u32 area, u8 layer, u32* blockIndexOut = nullptr)
    {
        TileLayer* tileLayer = TilesetMgr::instance->getTileLayer(area, layer);

        if (!tileLayer)
            return nullptr;

        return tileLayer->getTilePtr(x, y, blockIndexOut);
    }

    static inline u16* getTilePtrCurrentArea(u16 x, u16 y, u8 layer, u32* blockIndexOut = nullptr)
    {
        return getTilePtr(x, y, LevelInfo::instance->area, layer, blockIndexOut);
    }
};
