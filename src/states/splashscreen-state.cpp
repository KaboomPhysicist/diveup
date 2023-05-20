#include "states/splashscreen-state.h"

void SplashscreenState::init() { 
    SplashScreen *splashscreen = new SplashScreen();
    visibleObjectManager.add("splashscreen", splashscreen);
}

void SplashscreenState::handleInput(sf::Event *event) { }

void SplashscreenState::update(float timeElapsed) { 
    visibleObjectManager.updateAll(timeElapsed);
}

void SplashscreenState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}
SplashscreenState::~SplashscreenState() { }