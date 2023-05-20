#include "objects/gui/exit-button.h"
#include "diveup.h"

ExitButton :: ExitButton() : VisibleObject("assets/exit-btn.png"){}

void ExitButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            std::cout << "ExitButton Pressed" << std::endl;
            DiveUp::setState(DiveUp::Exiting);
        }
    }
}

void ExitButton::update(float timeElapsed) { }