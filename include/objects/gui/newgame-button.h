#pragma once

#include "objects/visible-object.h"

class NewGameButton : public VisibleObject {
    public:
        NewGameButton();
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
};