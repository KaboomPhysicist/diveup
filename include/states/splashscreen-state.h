#pragma once
#include "states/game-state.h"
#include "objects/gui/splashscreen.h"

class SplashscreenState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        ~SplashscreenState() override;
};