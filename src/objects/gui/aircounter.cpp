#include "objects/gui/aircounter.h"
#include "objects/entities/diver.h"
#include "diveup.h"

AirCounter:: AirCounter(int x,int y,float Oxygen) : VisibleObject("assets/bubble1.png"){

    //_sprite.setColor(sf::Color(255,255,255,opasity));
    oxygen = Oxygen;
    
    sf::Vector2f targetSize(x, y); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
}
void AirCounter::handleInput(sf::Event *event){}
void AirCounter::update(float timeElapsed){
    if(oxygen > 0){
        if (oxygen = 100){
            setOpacity(255);
        }
        else{
            setOpacity(255*(oxygen/10));
        }

    }
    else{
        DiveUp::setState(DiveUp::Gameover);
    }
}
void AirCounter::setOpacity(int opasity){
    _sprite.setColor(sf::Color(255,255,255,opasity));
}
