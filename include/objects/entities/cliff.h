# pragma once
#include "objects/visible-object.h"
#include "collision.h"


class Cliff: public VisibleObject {
public:
    Cliff(int,int,float,float);
    void update(float timeElapsed);
    void handleInput(sf::Event *event);
    void scaleCliff(float, float);
    static void verifyCliffs(std::vector<Cliff*> &, Cliff& );
    static void generateCliffs(std::vector<Cliff*> &cliffs, float velocity, int cliffsMax);
    static void verifySpace(std::vector<Cliff*> &_cliffs, Cliff &cliff);

    void collideWith(VisibleObject *target);

    private:
        float velocity;
};