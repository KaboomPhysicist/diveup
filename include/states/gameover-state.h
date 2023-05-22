#pragma once
#include "game-state.h"

#include "objects/gui/gameoverscreen.h"

#include "objects/gui/exit-button.h"
#include "objects/gui/playagain-button.h"

class gameoverState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;

        ~gameoverState() override;
};