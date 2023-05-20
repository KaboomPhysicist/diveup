#include "objects/gui/newgame-button.h"
#include "diveup.h"

NewGameButton :: NewGameButton() : VisibleObject("assets/newgame-btn.png"){}

void NewGameButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            std::cout << "New Game Button Pressed" << std::endl;
            DiveUp::setState(DiveUp::Playing);
        }
    }
}

void NewGameButton::update(float timeElapsed) { }