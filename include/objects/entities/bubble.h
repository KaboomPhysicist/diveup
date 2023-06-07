#pragma once

#include "objects/visible-object.h"
#include "objects/visible-object-manager.h"
#include "objects/entities/diver.h"
#include "objects/entities/cliff.h"
#include <vector>

class Bubble : public VisibleObject {
    public:
        Bubble(sf::Rect<float> constraints, float factor, float velocity_bias);
        void update(float timeElapsed) override;
        void collideWith(VisibleObject *target) override;
        
        void setBias(float bias);
        static void GenerateBubble(short int index, float velocity_factor, float velocity_bias, sf::Rect<float> constraints, std::vector<int> SCREEN_RANGE, std::vector<Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager);
        static void initBubbles(short int bubbleMax, float velocity_factor, float velocity_bias, sf::Rect<float> constraints, std::vector<int> SCREEN_RANGE, std::vector <Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager);
        bool isDead;

    private:
        float lifetime;
        float maxlifetime;
        float size;
        float velocity_factor;
        float velocity_bias;
        sf::Rect<float> constraints;

        float yVelocity();
        float xVelocity();

};
