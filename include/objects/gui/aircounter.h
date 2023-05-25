#pragma once
#include "objects/visible-object.h"


class AirCounter : public VisibleObject {
    public:
        AirCounter(int,int);
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
        void setOpacity(int);

        private:
            float oxygen;
};