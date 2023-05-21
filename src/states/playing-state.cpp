#include "states/playing-state.h"

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

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
    visibleObjectManager.add("cliff1", cliff1);
 }

void PlayingState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void PlayingState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void PlayingState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}



PlayingState::~PlayingState() { }