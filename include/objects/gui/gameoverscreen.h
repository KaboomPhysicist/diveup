#pragma once

#include "objects/visible-object.h"

class GameOverScreen : public VisibleObject {
    public:
        GameOverScreen();
        void update(float timeElapsed);
};