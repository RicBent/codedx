#pragma once

#include "sead.h"


class Level : public sead::IDisposer
{
public:

    class Area
    {
    public:
        struct Location
        {
            u16 x;      // 0
            u16 y;      // 2
            u16 w;      // 4
            u16 h;      // 6
            u8 id;      // 8
        };

    public:
        Location* getLocation(Rect* rectOut, u8 id);

        u32 id;                         // 0
        void* blocks[15];               // 4
        u32 blockSizes[15];             // 40
        u32 blockEntryCounts[15];       // 7C
        u8 _B8[0x100];                  // B8
        u8 _1B8[0x100];                 // 1B8
        u8 _2B8[0x100];                 // 2B8
    };

    Area* getArea(u32 id);

    static Level* instance;

    Area areas[4];
};


class LevelInfo : public sead::IDisposer
{
public:
    static LevelInfo* instance;

    u8 world;                   // 10
    u8 level;                   // 11
    u8 area;                    // 12
    u8 entrance;                // 13
    u32 zone;                   // 14
    u32 entranceType;           // 18
    u8 destWorld;               // 1C
    u8 destLevel;               // 1D
    u8 destArea;                // 1E
    u8 destEntrance;            // 1F
    u32 destZone;               // 20
    u32 destEntranceType;       // 24
};
