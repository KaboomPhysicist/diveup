#include "states/playing-state.h"
#include "objects/entities/diver.h"

void PlayingState::init() {

    Field *field = new Field();
    diver *diver1 = new diver(0,400);
    //field->setPosition(100, 200);
    diver1->setPosition(100, 200);
    
    field->setPriority(0);
    diver1->setPriority(1);

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
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