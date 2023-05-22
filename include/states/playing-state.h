#pragma once
#include "game-state.h"

#include "objects/entities/field.h"
#include "objects/entities/diver.h"
#include "objects/entities/cliff.h"
#include "objects/entities/bubble.h"
#include "diveup.h"



class PlayingState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        void BubblePopulation();
        //void scroll(float x, float y) override;
        ~PlayingState() override;
        
        void generateCliffs(std::vector<Cliff*> cliffs);
        void verifyCliffPos(int,int);

    private:
        float velocity;
        std::vector<Cliff*> _cliffs;
        int _cliffsMax;
        short int _bubbleMax;
        std::vector<Bubble*> _bubbles;

};
