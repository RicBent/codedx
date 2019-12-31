#pragma once

#include "model.h"

class DrawMgr
{
public:
    static DrawMgr* instance;

    void drawModel(Model* model);
    void drawTile(u16 tile, const Vec3& position, const u32& rotation, const Vec3& scale);

    inline void drawModel(ModelWrapper* modelWrapper)
    {
        drawModel(modelWrapper->model);
    }
};
