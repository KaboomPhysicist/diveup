#include "objects/gui/aircounter.h"
#include "objects/entities/diver.h"
#include "diveup.h"

AirCounter:: AirCounter(int x,int y) : VisibleObject("assets/bubble1.png"){  
    sf::Vector2f targetSize(x, y); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);
}
void AirCounter::handleInput(sf::Event *event){}
void AirCounter::update(float timeElapsed){}

void AirCounter::setOpacity(int opacity){

    if (opacity >= 20) {
        opacity = 255;
    } else if (opacity >= 15 && opacity <= 20) {
        opacity = 255 * 0.5;
    } else if (opacity >= 10 && opacity <= 15) {
        opacity = 255 * 0.25;
    } else if (opacity >= 5 && opacity <= 10) {
        opacity = 255 * 0.125;
    }else if (opacity >= 0 && opacity <= 5) {
        opacity = 0;
    }

    _sprite.setColor(sf::Color(255,255,255,opacity));
}
