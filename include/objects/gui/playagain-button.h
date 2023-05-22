#pragma once

#include "objects/visible-object.h"

class PlayAgain : public VisibleObject {
    public:
        PlayAgain();
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
};