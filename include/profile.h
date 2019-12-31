#pragma once

#include "types.h"
#include "resarchive.h"
#include "sead.h"
#include "preprocessor.h"
#include "profileid.h"

class Actor;
struct ActorInfo;
struct ActorBuildInfo;

class Profile
{
public:
    Profile(Actor* (*buildFunc)(const ActorBuildInfo*), u32 id, const sead::SafeString& name, const ActorInfo* actorInfo, u32 flags);
    virtual u32 vf00();                         // Returns 1

    ResArchive* getResArchiveById(u32 idx);

    static Profile* get(u32 id);
    static s16 getPriority(u32 id);
    static u8 getHasResources(u32 id);
    static u8 getResourceCount(u32 id);
    static const sead::SafeString* getResourceList(u32 id);


    Actor* (*buildFunc)(const ActorBuildInfo*); // 4
    u32 id;                                     // 8
    const ActorInfo* actorInfo;                 // C
    u8 hasResourcesLoaded;                      // 10
    u32 flags;                                  // 14


    static u32 spriteToProfileList[];


    static const u32 NUM_PROFILES_ORIGINAL  = 914;
    static const u32 NUM_PROFILES_CUSTOM    = ProfileId::Num - NUM_PROFILES_ORIGINAL;
    static const u32 NUM_PROFILES           = NUM_PROFILES_ORIGINAL + NUM_PROFILES_CUSTOM;

    static u32 getNumProfiles();


    static Profile* profilesOriginal[NUM_PROFILES_ORIGINAL];
    static Profile* profilesCustom[NUM_PROFILES_CUSTOM];

    static const s16 prioritiesOriginal[NUM_PROFILES_ORIGINAL];
    static s16 prioritiesCustom[NUM_PROFILES_CUSTOM];

    static const u8 hasResourcesOriginal[NUM_PROFILES_ORIGINAL];
    static u8 hasResourcesCustom[NUM_PROFILES_CUSTOM];

    static const u8 resourceCountOriginal[NUM_PROFILES_ORIGINAL];
    static u8 resourceCountCustom[NUM_PROFILES_CUSTOM];

    static const sead::SafeString* resourceListsOriginal[NUM_PROFILES_ORIGINAL];
    static const sead::SafeString* resourceListsCustom[NUM_PROFILES_CUSTOM];
};


struct ProfileResources
{
    ProfileResources(u32 id, u32 count, const sead::SafeString resources[])
    {
        if (id < Profile::NUM_PROFILES_ORIGINAL || id >= Profile::NUM_PROFILES)
            return;

        u32 customId = id - Profile::NUM_PROFILES_ORIGINAL;
        Profile::hasResourcesCustom[customId] = count > 0;
        Profile::resourceCountCustom[customId] = count;
        Profile::resourceListsCustom[customId] = resources;
    }
};

#define PROFILE_RESOURCES_IDENT(ident, id, ...)                                                                                 \
    const sead::SafeString PP_CONCAT(profileResourceFiles, ident)[] = { __VA_ARGS__ };                                          \
    const ProfileResources PP_CONCAT(profileResources, ident)(id, PP_NARG(__VA_ARGS__), PP_CONCAT(profileResourceFiles, ident))

#define PROFILE_RESOURCES(id, ...)   \
    PROFILE_RESOURCES_IDENT(__COUNTER__, id, __VA_ARGS__)
