#pragma once
#include "game-state.h"

#include "objects/entities/field.h"
#include "objects/entities/diver.h"
#include "objects/entities/cliff.h"
#include "objects/entities/bubble.h"

class DebugState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;

        ~DebugState() override;
        
    private:
        Diver *diver1;
        Cliff *cliff;
};