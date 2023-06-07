#include "objects/gui/playagain-button.h"
#include "diveup.h"
#include "states/splashscreen-state.h"

PlayAgain :: PlayAgain() : VisibleObject("assets/playagain-btn.png"){}

void PlayAgain::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            std::cout << "Play again Button Pressed" << std::endl;
            DiveUp::setState(DiveUp::Splashscreen);
        }
    }
    else if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Return) {
            DiveUp::setState(DiveUp::Splashscreen);
        }
    }
}

void PlayAgain::update(float timeElapsed) { }