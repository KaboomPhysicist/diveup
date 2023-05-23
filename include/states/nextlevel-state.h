#pragma once
#include "game-state.h"

#include "objects/gui/nextlevel-button.h"

class NextLevelState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        ~NextLevelState() override;
        
    private:
        int _level;
        int _lineposition;
};