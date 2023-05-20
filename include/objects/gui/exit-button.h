#pragma once

#include "objects/visible-object.h"

class ExitButton : public VisibleObject {
    public:
        ExitButton();
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
};