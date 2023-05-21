#include "states/playing-state.h"
#include <iostream>

void PlayingState::init() {
    std::cout << "PlayingState::init()" << std::endl;

    Field *field = new Field();
    //field->setPosition(100, 200);
    
    field->setPriority(0);

    visibleObjectManager.add("field", field);
 }



void PlayingState::handleInput(sf::Event *event) { }
void PlayingState::update(float timeElapsed) { }
void PlayingState::draw(sf::RenderWindow *window) { }
PlayingState::~PlayingState() { }