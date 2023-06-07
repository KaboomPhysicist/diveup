#pragma once
#include "states/game-state.h"
#include "objects/gui/splashscreen.h"

#include <vector>

#include "objects/gui/newgame-button.h"
#include "objects/gui/exit-button.h"
#include "objects/entities/bubble.h"
#include <SFML/Audio.hpp>




class SplashscreenState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        void BubblesEffect();
        ~SplashscreenState() override;
    private:
        short int _bubbleMax;
        std::vector<Bubble*> _bubbles;
        std::vector<int> SCREEN_RANGE;
        sf::Rect<float> bubble_constraints;
        
};