#include "states/nextlevel-state.h"
#include "diveup.h"

void NextLevelState::init() {
    NextLevelButton *nextLevelButton = new NextLevelButton();
    Field *field = new Field();

    nextLevelButton->setPosition(95, 360);
    nextLevelButton->setPriority(1);
    field->setPriority(0);

    visibleObjectManager.add("nextLevelButton", nextLevelButton);
    visibleObjectManager.add("field", field);
}

void NextLevelState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void NextLevelState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void NextLevelState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

NextLevelState::~NextLevelState() {
}