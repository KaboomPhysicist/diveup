#include "objects/gui/newgame-button.h"
#include "diveup.h"
#include "states/splashscreen-state.h"

NewGameButton :: NewGameButton() : VisibleObject("assets/newgame-btn.png"){}

void NewGameButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            //std::cout << "New Game Button Pressed" << std::endl;
            //dynamic_cast<SplashscreenState*>(DiveUp::getState())->stopMusic();

            DiveUp::setState(DiveUp::Playing);
        }
    }
    else if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Return) {
            DiveUp::setState(DiveUp::Playing);
        }
    }
}

void NewGameButton::update(float timeElapsed) { }