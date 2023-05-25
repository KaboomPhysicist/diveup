#pragma once
#include "objects/visible-object.h"


class AirCounter : public VisibleObject {
    public:
        AirCounter(int,int,float);
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
        void setOpacity(int);

        private:
            float oxygen;
};