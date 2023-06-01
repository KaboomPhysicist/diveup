#include "states/nextlevel-state.h"
#include "diveup.h"

void NextLevelState::init() {
    NextLevelButton *nextLevelButton = new NextLevelButton();

    sf::Vector2f targetSize(300/2, 80/2); 
    ExitButton *exitButton = new ExitButton(targetSize);
    
    NextLevel *field = new NextLevel();


    nextLevelButton->setPosition(240 - 75, 80);
    nextLevelButton->setPriority(1);

    exitButton->setPosition(240 - 75, 130);
    exitButton->setPriority(1);

    field->setPriority(0);

    visibleObjectManager.add("nextLevelButton", nextLevelButton);
    visibleObjectManager.add("exitButton", exitButton);
    visibleObjectManager.add("field", field);
}

void NextLevelState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void NextLevelState::setDiver(Diver diver){
    *_diver = diver;
}

void NextLevelState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void NextLevelState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

NextLevelState::~NextLevelState() {
}