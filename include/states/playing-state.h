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
        ~PlayingState() override;
        
        void newLevel();
        void initAirmarker(int, int);
        void opacityupdate(int);

        void reset();
        void setEnded(bool);
        void resetLevel();
    private:
        float velocity;

        std::vector<Cliff*> _cliffs;
        std::vector<AirCounter*> _aircounters;
        std::vector<Bubble*> _bubbles;

        short int _bubbleMax;
        float _ascendingSpeed;
        short int _level;
        bool _end;
        sf::Rect<float> bubble_constraints;
        Diver *diver1;
        FinishLine *finishline;
        std::vector<int> SCREEN_RANGE;
};
