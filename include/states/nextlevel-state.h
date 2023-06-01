#pragma once
#include "game-state.h"

#include "objects/gui/nextlevel-button.h"
#include "objects/gui/nextlevel.h"
#include "objects/entities/diver.h"

class NextLevelState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        ~NextLevelState() override;
        void setDiver(Diver);
        
    private:
        int _level;
        int _lineposition;
        Diver *_diver;
        float _diverPosition;
};
