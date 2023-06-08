#include "objects/gui/nextlevel-button.h"
#include "diveup.h"

NextLevelButton :: NextLevelButton() : VisibleObject("assets/nextlevel-btn.png"){
    sf::Vector2f targetSize(300/2, 80/2); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
}

void NextLevelButton::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        if (getBoundingRect().contains(x, y)){
            //std::cout << "Next Level Button Pressed" << std::endl;
            
            DiveUp::setState(DiveUp::Playing);
        }
    }
    if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Enter) {
        DiveUp::setState(DiveUp::Playing);
    }
}
