#pragma once
#include "objects/visible-object.h"

class ExitButton : public VisibleObject {
    public:
        ExitButton(sf::Vector2f targetSize);
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
};