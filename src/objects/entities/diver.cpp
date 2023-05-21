#include "objects/entities/diver.h"

diver::diver(float constraintLeft, float constraintRight) : VisibleObject("assets/diver-right.png") {
    _constraintLeft = constraintLeft;
    _constraintRight = constraintRight;

    sf::Vector2f targetSize(80.0f, 80.0f); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
}

void diver::Set_texture(std::string textureFilename) {
    if (!_texture.loadFromFile(textureFilename)) {
        std::cout << "Error while loading asset" << std::endl;
        return;
    }
    _isLoaded = true;
    _sprite.setTexture(_texture);

}

void diver::handleInput(sf::Event *event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Left) {
            _direction = Left;
            diver::Set_texture("assets/diver-left.png");
        } else if (event->key.code == sf::Keyboard::Right) {
            _direction = Right;
            diver::Set_texture("assets/diver-right.png");
        }
    } else if (event->type == sf::Event::KeyReleased) {
            _direction = NONE;
            diver::Set_texture("assets/stand-diver.png");
        }
    }


void diver::update(float timeElapsed) {


    float velocity = 0.0f;

       if (_direction == Left) {
        velocity = _speed * -1;
    } else if (_direction == Right) {
        velocity = _speed;
    }
    
    move(velocity * timeElapsed,0);

    if (getPosition().x < _constraintLeft) {
        setPosition(_constraintLeft, getPosition().y);
    } else if (getPosition().x > _constraintRight) {
        setPosition(_constraintRight, getPosition().y);
    }
}