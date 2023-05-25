#include "objects/entities/cliff.h"
#include "diveup.h"

Cliff::Cliff(int sizex, int sizey,float dir,float speed) : VisibleObject("assets/cliff1.png") { 
    sf::Vector2f targetSize(sizex, sizey); 
    if (dir == 1.0f) {
        this->_sprite.setScale(
                            -targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
    } else {
        this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
    }

    
    velocity = speed;
}


void Cliff::collideWith(VisibleObject *target) {
    if(!dynamic_cast<Diver*>(target) ) return;
    
    std::cout << "Te diste un tiestaso" << std::endl;
    update();
    dynamic_cast<PlayingState*>(DiveUp::getState())->setEnded(true);
    dynamic_cast<PlayingState*>(DiveUp::getState())->resetLevel();

    DiveUp::setState(DiveUp::Gameover);
};


void Cliff::update(float timeElapsed) { 

    move(0, velocity * timeElapsed);
}

void Cliff::scaleCliff(float x, float y) {
    sf::Vector2f targetSize(x, y); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
}

void Cliff::handleInput(sf::Event *event){}