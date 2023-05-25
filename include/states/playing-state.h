#pragma once
#include "game-state.h"

#include "objects/entities/field.h"
#include "objects/entities/diver.h"
#include "objects/entities/cliff.h"
#include "objects/entities/bubble.h"
#include "objects/entities/finishline.h"
#include "objects/gui/aircounter.h"
#include "diveup.h"
#include <random>



class PlayingState : public GameState{
    public:
        void init() override;
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void draw(sf::RenderWindow *window) override;
        void BubblePopulation();
        //void scroll(float x, float y) override;
        ~PlayingState() override;
        
        void newLevel();
        void airmarker(int, int,float);

        void generateCliffs(std::vector<Cliff*> cliffs,float,int);
        void verifyCliffs(Cliff&);
        void verifySpace(Cliff&);
        void scaleCliffs(float, float,Cliff*);


    private:
        float velocity;
        std::vector<Cliff*> _cliffs;


        std::vector<AirCounter*> _aircounters;

        short int _bubbleMax;
        std::vector<Bubble*> _bubbles;
        float _ascendingSpeed;
        short int _level;
        sf::Rect<float> bubble_constraints;
        Diver *diver1;
        FinishLine *finishline;
        std::vector<int> SCREEN_RANGE;
};
