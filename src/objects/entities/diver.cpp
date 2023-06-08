#include "objects/entities/diver.h"
#include "states/playing-state.h"
#include "objects/entities/bubble.h"


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
        if (event->key.code == sf::Keyboard::Left or event->key.code == sf::Keyboard::A) {
            _direction = Left;
            this->Set_texture("assets/diver-left.png");
        } else if (event->key.code == sf::Keyboard::Right or event->key.code == sf::Keyboard::D) {
            _direction = Right;
            this->Set_texture("assets/diver-right.png");
        } else if (dynamic_cast<DebugState*>(DiveUp::getState())){
            if (event->key.code == sf::Keyboard::Up){
                _direction = Up;
            } else if (event->key.code == sf::Keyboard::Down){
                _direction = Down;
            }
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
    } else if (_direction == Up) {
        y_velocity = -80;
    } else if (_direction == Down) {
        y_velocity = 80;}
    else y_velocity = 0;


    move(x_velocity * timeElapsed, y_velocity * timeElapsed);

    if (getPosition().x < _constraintLeft) {
        setPosition(_constraintLeft, getPosition().y);}
    else if (getPosition().x > _constraintRight) {
        setPosition(_constraintRight, getPosition().y);}
}

void Diver::collideWith(VisibleObject *target){
    if(dynamic_cast<Bubble*>(target)){
        _oxygen += 3;
        //std::cout << "Oxygen: " << _oxygen << std::endl;
    }

    if(dynamic_cast<Cliff*>(target) ){
    
        std::cout << "Te diste un tiestaso" << std::endl;
        // Check if State is PlayingState
        if(!dynamic_cast<PlayingState*>(DiveUp::getState())) return;

        dynamic_cast<PlayingState*>(DiveUp::getState())->setEnded(true);
        dynamic_cast<PlayingState*>(DiveUp::getState())->resetLevel();

        DiveUp::setState(DiveUp::Gameover);
    }

}

void Diver::setFinishing(bool val){
    _finishing = val;
}

std::vector<sf::Vector2f> Diver::calculateAxes() {
    std::vector<sf::Vector2f> axes;
    sf::Vector2f axis1(0, 1);
    sf::Vector2f axis2(1, 0);

    /*if (_direction == Left){
        axis1 = sf::Vector2f(1, 0);
        axis2 = sf::Vector2f(-23, 11);
    }
    else if (_direction == Right){
        axis1 = sf::Vector2f(1, 0);
        axis2 = sf::Vector2f(11, 23);
    }*/

    axes.push_back(axis1);
    axes.push_back(axis2);

    return axes;
}

sf::Vector2f Diver::projectOntoAxis(const sf::Vector2f& axis) {
    float minProjection = std::numeric_limits<float>::max();
    float maxProjection = -std::numeric_limits<float>::max();

    sf::Vector2f vertices[4];

    // Find the vertices of the rectangular diver
    //if (_direction == NONE){
        vertices[0] = sf::Vector2f(getLeft() + 4, getTop());
        vertices[1] = sf::Vector2f(getRight() - 4, getTop());
        vertices[2] = sf::Vector2f(getRight() -4, getBottom());
        vertices[3] = sf::Vector2f(getLeft() + 4, getBottom());

    //}
    //std::cout << "minProjection: " << minProjection << "maxProjection: " << maxProjection << std::endl;

   /* else if (_direction == Left){

        vertices[0] = sf::Vector2f(getLeft() + 1, getTop());
        vertices[1] = sf::Vector2f(getRight() - 13, getTop());
        vertices[2] = sf::Vector2f(getRight(), getBottom() - 5);
        vertices[3] = sf::Vector2f(getLeft() + 12, getBottom() - 5);
    }

    else if (_direction == Right){
        vertices[0] = sf::Vector2f(getRight() - 1, getTop());
        vertices[1] = sf::Vector2f(getLeft() + 13, getTop());
        vertices[2] = sf::Vector2f(getLeft(), getBottom() - 5);
        vertices[3] = sf::Vector2f(getRight() - 12, getBottom() - 5);
    }*/

    for(int i = 0; i < 4; i++){
            //std::cout << "Vertex" << " " <<vertices[i].x << " " << vertices[i].y << std::endl;
            float projection = axis.x * (vertices[i].x)+ axis.y * (vertices[i].y);
            minProjection = std::min(minProjection, projection);
            maxProjection = std::max(maxProjection, projection);
            }

    return sf::Vector2f(minProjection, maxProjection);

}
