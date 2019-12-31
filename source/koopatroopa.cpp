#include "actor/enemy.h"

class KoopaTroopa : public Enemy     // actually inherits ShellEnemy
{
public:
    bool decideFirstStateCustom();

    DECLARE_STATE(KoopaTroopa, Slide);
};


bool KoopaTroopa::decideFirstStateCustom()
{
    if (settings2 & 0x100000)
    {
        doStateChange(&StateID_Slide);
        return true;
    }

    return false;
}
