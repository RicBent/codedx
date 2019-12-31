#include "actor/stageactor.h"

#include "lightsource.h"
#include "mask.h"
#include "movementhandler.h"

class LightActor : public StageActor
{
public:
    LightActor(const ActorBuildInfo* buildInfo);
    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    MovementHandler movementHandler;

    LightSource lightSource;
    u32 lightType;
    sead::Color4f lightColor;
    f32 lightAttenuationRadius;

    LightMask lightMask;
    f32 lightMaskRadius;
};

const Profile lightActorProfile(&LightActor::build, ProfileId::LightActor, "LightActor", nullptr, 0);


LightActor::LightActor(const ActorBuildInfo* buildInfo) : StageActor(buildInfo) { }

Actor* LightActor::build(const ActorBuildInfo* buildInfo)
{
    return new LightActor(buildInfo);
}


u32 LightActor::onCreate()
{
    lightType = settings1 >> 24;

    lightColor =
    {
        ((settings1 >> 16) & 0xFF) / 255.0f,
        ((settings1 >> 8) & 0xFF) / 255.0f,
        (settings1 & 0xFF) / 255.0f,
        1.0f
    };

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    lightAttenuationRadius = (settings2 >> 24) * 0.25f;
    lightSource.update(lightType, &position, nullptr, &lightAttenuationRadius, nullptr, &lightColor, nullptr, nullptr);

    lightMaskRadius = ((settings2 >> 8) & 0xFF) * 8.0f;
    lightMask.init(nullptr, (settings2 >> 16) & 0xFF);
    lightMask.radius = lightMaskRadius;
    lightMask.position = position;
    lightMask.update();

    return 1;
}

u32 LightActor::onExecute()
{
    movementHandler.execute();
    position = movementHandler.position;

    lightMask.radius = lightMaskRadius;
    lightMask.position = position;
    lightMask.update();

    lightSource.update(lightType, &position, nullptr, &lightAttenuationRadius, nullptr, &lightColor, nullptr, nullptr);

    return 1;
}

u32 LightActor::onDraw()
{
    lightMask.draw();
    return 1;
}
