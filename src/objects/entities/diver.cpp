#include "objects/entities/diver.h"

Diver::Diver(float constraintLeft, float constraintRight) : VisibleObject("assets/stand-diver3.png") {
    _constraintLeft = constraintLeft;
    _constraintRight = constraintRight;

    sf::Vector2f targetSize(80.0f, 80.0f); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);

    _oxygen = 10;
}

void Diver::Set_texture(std::string textureFilename) {
    if (!_texture.loadFromFile(textureFilename)) {
        std::cout << "Error while loading asset" << std::endl;
        return;
    }
    _isLoaded = true;
    _sprite.setTexture(_texture);

}

void Diver::handleInput(sf::Event *event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Left) {
            _direction = Left;
            this->Set_texture("assets/DEBUG-diver-left.png");
        } else if (event->key.code == sf::Keyboard::Right) {
            _direction = Right;
            this->Set_texture("assets/DEBUG-diver-right.png");
        }
    } else if (event->type == sf::Event::KeyReleased) {
            _direction = NONE;
            this->Set_texture("assets/stand-diver3.png");
        }
    }


float Diver::getOxygen() {
    return _oxygen;}

void Diver::setOxygen(float oxygen) {
    _oxygen = oxygen;
}
    
void Diver::update(float timeElapsed) {


    float x_velocity = 0.0f;

       if (_direction == Left) {
        x_velocity = _speed * -1;
    } else if (_direction == Right) {
        x_velocity = _speed;
    }

    if(_finishing){
        y_velocity = -400;
    }
    else y_velocity = 0;

    
    move(x_velocity * timeElapsed, y_velocity * timeElapsed);

    if (getPosition().x < _constraintLeft) {
        setPosition(_constraintLeft, getPosition().y);
    } else if (getPosition().x > _constraintRight) {
        setPosition(_constraintRight, getPosition().y);
    }
}

void Diver::collideWith(VisibleObject *target){
    if(!dynamic_cast<Bubble*>(target)) return;

    _oxygen += 3;
    std::cout << "Oxygen: " << _oxygen << std::endl;

}

void Diver::setFinishing(bool val){
    _finishing = val;
}