#include "objects/entities/bubble.h"
#include <cmath>

Bubble::Bubble(sf::Rect<float> constraints) : VisibleObject("assets/bubble.png") {
    // Apply transparency to the sprite. Last value is the alpha value.
    this->_sprite.setColor(sf::Color(255, 255, 255, 128));

    this->constraints = constraints;
    this->maxlifetime = 4;
    this->lifetime = 0;
    this->speed = 100;
    this->direction = 0;
    this->size = 10;
    this->isDead = false;
}


void Bubble::update(float timeElapsed){
    if(isDead) return;

    lifetime += timeElapsed;

    if(lifetime>maxlifetime){
        this->isDead = true;
        std::cout << "Bubble is dead" << std::endl;
    }


    float dispY = -yVelocity() * timeElapsed;
    float dispX = 0;

    move(dispX, dispY);

}

float Bubble::yVelocity(){
    float rho = 1;
    float g = 9.81;
    float A = 3.14*size*size;
    float Cd = 0.47;
    float m = 1;
    float v = std::sqrt(2 * m * g / (rho * A * Cd)) * std::tanh(lifetime * std::sqrt((rho * A * Cd * g) / (2 * m)));

    return v;
}

void Bubble::collideWith(VisibleObject *target) {};
