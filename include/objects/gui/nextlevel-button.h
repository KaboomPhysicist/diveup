#pragma once

#include "objects/visible-object.h"

class NextLevelButton : public VisibleObject {
    public:
        NextLevelButton();
        void handleInput(sf::Event *event);
        void update(float timeElapsed){};
};