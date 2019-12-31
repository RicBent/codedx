#pragma once

#include "states.h"
#include "util/vec2.h"

class LineFollower  // size: 0x90
{
public:
    void init(const Vec2& position, u8 layer, bool noReverseOnStop, bool reveredDirection);
    void start(bool unk);

    inline void execute()
    {
        states.execute();
    }

    StateWrapper<LineFollower> states;  // 0
    Vec2 _24[7];                        // 24
    Vec2 speed;                         // 5C
    Vec2 position;                      // 64
    Vec2 lastPosition;                  // 6C
    Vec2 blockPosition;                 // 74
    Vec2 _7C;                           // 7C
    u32 rotation;                       // 84
    f32 lineSpeed;                      // 88
    bool noReverseOnStop;               // 8C
    u8 layer;                           // 8D
    bool reversedDirection;             // 8E
    u8 _8F;                             // 8F
};
