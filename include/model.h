#pragma once

#include "sead.h"
#include "util/mtx34.h"
#include "resarchive.h"

class Model     // this has 2 base classes
{
    SEAD_RTTI_BASE(Model)

public:
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();                        // used during update
    virtual void vf38();                        // used during update
    virtual void setMtx(const Mtx34& mtx);
    virtual void vf40();
    virtual void setScale(const Vec3& scale);
    virtual void vf48();
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6C();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8C();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98();
    virtual void vf9C();
    virtual void vfA0();
    virtual void vfA4();
    virtual void vfA8();
    virtual void vfAC();
    virtual void vfB0();
    virtual void vfB4();
    virtual void vfB8();
    virtual void vfBC();
    virtual void** getSklAnims();
    virtual void** getTexAnims();
    virtual void** getShuAnims();
    virtual void** getVisAnims();
    virtual void** getShaAnims();
};


struct Animation
{
    enum Flags
    {
        FlagRepeat  = 1 << 0,
        FlagUnk2    = 1 << 1,
    };

    void setRepeat(bool repeat);

    f32 startFrame; // 0    Inited to 0.0
    f32 endFrame;   // 4    Inited to 1.0
    f32 _8;         // 8    Inited to 0.0
    f32 _C;         // C    Inited to 1.0
    f32 frame;      // 10   Inited to 0.0
    f32 speed;      // 14   Inited to 1.0
    u32 flags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class ModelAnimation : public Animation
{
public:
    ModelAnimation();
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation  // size: 0x8C
{
public:
    SkeletalAnimation();
    void calculate() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

    // nn::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation
{
public:
    TextureAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public ModelAnimation
{
public:
    ShaderAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};


template <class T>
struct AnimationList
{
    s32 count;      // 4
    T** anims;      // 8

    T* operator[](s32 i)
    {
        return anims[i];
    }
};


class ModelWrapper
{
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtx)
    {
        model->setMtx(mtx);
    }

    inline void setScale(const Vec3& scale)
    {
        model->setScale(scale);
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < sklAnims.count)
            sklAnims[idx]->play(archive, identifier);
    }

    inline void playTexAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < texAnims.count)
            texAnims[idx]->play(archive, identifier);
    }

    inline void playShuAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shuAnims.count)
            shuAnims[idx]->play(archive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0)
    {
        ResArchive* archive = ResArchiveMgr::instance->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, false, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

	Model* model;                               // 0
	ResArchive* archive;                        // 4
	AnimationList<SkeletalAnimation> sklAnims;  // 8
	AnimationList<TextureAnimation> texAnims;   // 10
	AnimationList<ShaderAnimation> shuAnims;    // 18
	AnimationList<Animation> visAnims;          // 20
	AnimationList<Animation> shaAnims;          // 28
};
