#pragma once

#include "sead/safestring.h"
#include "sead/idisposer.h"
#include "sead/random.h"


// TODO: Move to seperate files.

namespace sead {

class RuntimeTypeInfo
{
public:
    class Interface;
};

struct ListNode
{
    ListNode* previous;
    ListNode* next;
};

struct Color4f
{
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

}


#define SEAD_RTTI_BASE(CLASS)                                                                       \
    public:                                                                                         \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const;    \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;    

#define SEAD_RTTI_OVERRIDE(CLASS, BASE)                                                             \
    public:                                                                                         \
        bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const override;   \
        const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;

