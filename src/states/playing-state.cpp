#include "states/playing-state.h"
#include "diveup.h"

void PlayingState::init() {

    Field *field = new Field();
    diver *diver1 = new diver(0,400);
    Cliff *cliff1 = new Cliff();
    //field->setPosition(100, 200);
    diver1->setPosition(100, 200);
    cliff1->setPosition(0, 200);
    
    field->setPriority(0);
    cliff1->setPriority(1);
    diver1->setPriority(2);

    _bubbleMax = 15;
    _bubbles = std::vector<Bubble*>(_bubbleMax);

    std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
    Bubbles::initBubbles(_bubbleMax, 30, SCREEN_RANGE, this->_bubbles, visibleObjectManager);

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
    visibleObjectManager.add("cliff1", cliff1);
    std::cout << "PlayingState initialized" << std::endl;
 }

void PlayingState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void PlayingState::update(float timeElapsed) { 
    BubblePopulation();
    visibleObjectManager.updateAll(timeElapsed);
}

void PlayingState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

void PlayingState::BubblePopulation(){
        short int _bubbleIndex = 0;
        std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};


        for(Bubble* bubble : _bubbles){
            if(bubble->isDead){
                visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
                Bubbles::GenerateBubble(_bubbleIndex, 30, SCREEN_RANGE, _bubbles, visibleObjectManager);
            }
            _bubbleIndex++;
        }
}

PlayingState::~PlayingState() { }