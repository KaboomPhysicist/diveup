#include "objects/gui/exit-button.h"
#include "diveup.h"

ExitButton :: ExitButton(sf::Vector2f targetSize) : VisibleObject("assets/exit-btn.png"){
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
}

void ExitButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            //std::cout << "ExitButton Pressed" << std::endl;
            DiveUp::setState(DiveUp::Exiting);
        }
    }
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Escape) {
            DiveUp::setState(DiveUp::Exiting);
        }
    }
}

void ExitButton::update(float timeElapsed) { }