#include "states/splashscreen-state.h"

void SplashscreenState::init() { 
    // Add the backgroud
    SplashScreen *splashscreen = new SplashScreen();
    splashscreen->setPriority(0);

    // Add the buttons of the splashscreen/menu
    NewGameButton *newGameButton = new NewGameButton();
    newGameButton->setPosition(120, 400);
    newGameButton->setPriority(1);

    ExitButton *exitButton = new ExitButton();
    exitButton->setPosition(120, 450);
    exitButton->setPriority(1);

    Bubble *bubble = new Bubble(sf::Rect<float>(0, 0, 800, 600));
    bubble->setPosition(100, 100);
    bubble->setPriority(1);

    visibleObjectManager.add("splashscreen", splashscreen);
    visibleObjectManager.add("newGameButton", newGameButton);
    visibleObjectManager.add("exitButton", exitButton);
    visibleObjectManager.add("testbubble", bubble);
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

void SplashscreenState::BubblesEffect(){


}