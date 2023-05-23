#include "objects/gui/nextlevel-button.h"
#include "diveup.h"

NextLevelButton :: NextLevelButton() : VisibleObject("assets/nextlevel-btn.png"){}

void NextLevelButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            std::cout << "Next Level Button Pressed" << std::endl;
            
            DiveUp::setState(DiveUp::Playing);
        }
    }
}