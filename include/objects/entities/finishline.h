#pragma once
#include "objects/visible-object.h"
#include "collision.h"

class FinishLine: public VisibleObject {
    public:
        FinishLine(int position, float speed);
        void update(float timeElapsed) override;
        void handleInput(sf::Event *event) override;
        void collideWith(VisibleObject *target) override;
        void setFinishing(bool);
    private:
        float velocity;
        int position;
        bool _finishing;
};