#pragma once
#include "objects/visible-object.h"
#include "collision.h"

class FinishLine: public VisibleObject {
    public:
        FinishLine(int position, float speed);
        void update(float timeElapsed);
        void handleInput(sf::Event *event);
        void collideWith(VisibleObject *target);
        void setFinishing(bool);
    private:
        float velocity;
        int position;
        bool _finishing;
};