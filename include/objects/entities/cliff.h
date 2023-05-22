# pragma once
#include "objects/visible-object.h"
#include "collision.h"


class Cliff: public VisibleObject {
public:
    Cliff(int,int,float);
    void update(float timeElapsed);
    void handleInput(sf::Event *event);

    private:
        float velocity;
};