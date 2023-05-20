#include "states/splashscreen-state.h"

void SplashscreenState::init() { 
    // Add the backgroud
    SplashScreen *splashscreen = new SplashScreen();
    splashscreen->setPriority(0);

    // Add the buttons of the splashscreen/menu
    NewGameButton *newGameButton = new NewGameButton();
    newGameButton->setPosition(120, 500);
    newGameButton->setPriority(1);

    visibleObjectManager.add("splashscreen", splashscreen);
    visibleObjectManager.add("newGameButton", newGameButton);
}

void SplashscreenState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void SplashscreenState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void SplashscreenState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}
SplashscreenState::~SplashscreenState() { }