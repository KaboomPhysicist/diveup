#pragma once

#include "objects/visible-object.h"

class SplashScreen : public VisibleObject {
    public:
        SplashScreen();
        void update(float timeElapsed);
};