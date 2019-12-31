#pragma once

#include "nn/atk.h"
#include "util/vec2.h"


class SoundSystem
{
public:
    nn::atk::SoundArchive* getSoundArchive();
    
    inline const char* GetItemLabel(u32 id) { return getSoundArchive()->GetItemLabel(id); }
    inline u32 GetItemId(char const* label) { return getSoundArchive()->GetItemId(label); }


    static SoundSystem* instance;
};


class SoundActor : public nn::atk::SoundActor
{
public:
    u32 _7C;
	u32 _80;
	u32 _84;
	u32 _88;
};


class BasicSoundActor : public SoundActor
{
public:
    void playSound(const char* label, Vec2* screenPos, u32 unk);
};

// Both are dereived classes from BasicSoundActor
extern BasicSoundActor* GlobalBasicSoundActorA;
extern BasicSoundActor* GlobalBasicSoundActorB;


class MovingSoundActor : public SoundActor
{
public:
    class Handle : public sead::IDisposer
    {
    public:
        u32 _10;
        f32 _14;
    };

public:
    MovingSoundActor(u32 unk1, u32 unk2);
    void setPosition(const Vec2& position);

    u32 _8C;
    u32 _90;
    u32 _94;
    u32 _98;
    Handle handles[6];  // 9C
    u32 _12C;
    u32 _130;
};


// Convenience

void mapPositionToScreen(Vec2& out, const Vec2& position);

inline void PlaySound(const char* label, const Vec2& position)
{
    Vec2 screenPos;
    mapPositionToScreen(screenPos, position);
    GlobalBasicSoundActorA->playSound(label, &screenPos, 0);
}
