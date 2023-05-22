#pragma once

#include "objects/visible-object.h"
#include "objects/visible-object-manager.h"
#include "objects/entities/diver.h"
#include "objects/entities/cliff.h"
#include <vector>

class Bubble : public VisibleObject {
    public:
        Bubble(float factor);
        void update(float timeElapsed);
        void collideWith(VisibleObject *target);
        bool isDead;

    private:
        float lifetime;
        float maxlifetime;
        float size;
        float velocity_factor;

        float yVelocity();
        float xVelocity();

};

namespace Bubbles{
    void GenerateBubble(short int index, float velocity_factor, std::vector<int> SCREEN_RANGE, std::vector<Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager);
    void initBubbles(short int bubbleMax, float velocity_factor, std::vector<int> SCREEN_RANGE, std::vector <Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager);
}