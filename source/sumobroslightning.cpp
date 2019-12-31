#include "actor/multistateactor.h"
#include "arearumblemgr.h"

class SumoBrosLightning : public MultiStateActor
{
public:
    void setYSpeed();
    void onGroundTouch(StateBase* scheduledNextState);
};


void SumoBrosLightning::setYSpeed()
{
    if (settings2 & 0xFF)
        speed.y = (settings2 & 0xFF) * -1.0f;
    else
        speed.y = -2.0f;
}

void SumoBrosLightning::onGroundTouch(StateBase* scheduledNextState)
{
    if (settings2 & 0x100)
        isDeleted = true;
    else
        doStateChange(scheduledNextState);

    if (settings2 & 0x1000)
        AreaRumbleMgr::instance->rumble(21, 3, 0, 0);
}
