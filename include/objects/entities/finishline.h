#pragma once
#include "objects/visible-object.h"
#include "collision.h"

class FinishLine: public VisibleObject {
    public:
        FinishLine(int position);
        void update(float timeElapsed);
        void handleInput(sf::Event *event);
        void collideWith(VisibleObject *target);
    private:
        float velocity;
        int position;
};