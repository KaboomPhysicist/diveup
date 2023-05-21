#include "objects/entities/cliff.h"
#include "diveup.h"

Cliff::Cliff() : VisibleObject("assets/cliff1.png") { 
    sf::Vector2f targetSize(300, 300); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
    velocity = 0.0f;
}

void Cliff::update(float timeElapsed) { 

    move(0, velocity * timeElapsed);
}

void Cliff::handleInput(sf::Event *event){
    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        //sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        sf::Vector2f mousePosition = sf::Vector2f(x, y);
        sf::Uint8 alphaLimit = 127;

        const sf::Sprite sprite = this->_sprite;
        

        if(Collision::singlePixelTest(sprite, mousePosition, 128)){
            std::cout << "Cliff Pressed" << std::endl;
            if(velocity == 0.0f)
                velocity = 100.0f;
            else if(velocity == 100.0f)
                velocity = 0.0f;
        }
    }
}