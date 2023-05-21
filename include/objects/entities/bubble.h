#pragma once

#include "objects/visible-object.h"

class Bubble : public VisibleObject {
    public:
        Bubble(sf::Rect<float> constraints);
        void update(float timeElapsed);
        void collideWith(VisibleObject *target);
        bool isDead;

    private:
        float lifetime;
        float maxlifetime;
        sf::Rect<float> constraints;
        float size;

        float yVelocity();

};