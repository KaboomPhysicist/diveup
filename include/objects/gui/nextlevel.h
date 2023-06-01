#pragma once

#include "objects/visible-object.h"

class NextLevel : public VisibleObject {
    public:
        NextLevel();
        void update(float timeElapsed);
};