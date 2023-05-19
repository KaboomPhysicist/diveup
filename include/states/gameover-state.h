#pragma once
#include "game-state.h"

class gameoverState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
};