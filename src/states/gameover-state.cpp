#include "states/gameover-state.h"

void gameoverState::init() { 

    // Add the backgroud
    GameOverScreen *gameoverscreen = new GameOverScreen();
    gameoverscreen->setPriority(0);

    PlayAgain *playagainButton = new PlayAgain();
    playagainButton->setPosition(95, 360);
    playagainButton->setPriority(1);

    ExitButton *exitButton = new ExitButton(sf::Vector2f(300,80));
    exitButton->setPosition(95, 460);
    exitButton->setPriority(1);

    visibleObjectManager.add("gameoverscreen", gameoverscreen);
    visibleObjectManager.add("exitButton", exitButton);
    visibleObjectManager.add("playagainButton", playagainButton);
}

void gameoverState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void gameoverState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void gameoverState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

gameoverState::~gameoverState() { }