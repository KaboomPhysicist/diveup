# pragma once
#include "objects/visible-object.h"
#include "collision.h"


class Cliff: public VisibleObject {
public:
    Cliff();
    void update(float timeElapsed);
    void handleInput(sf::Event *event);
private:
    float velocity;
};