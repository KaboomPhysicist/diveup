#include "objects/entities/bubble.h"
#include <cmath>
#include <random>

Bubble::Bubble(sf::Rect<float> constraints) : VisibleObject("assets/bubble.png") {
    // Apply transparency to the sprite. Last value is the alpha value.
    //this->_sprite.setColor(sf::Color(255, 255, 255, 128));

    this->size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5)) + 22;

    sf::Vector2f targetSize(this->size, this->size); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);

    this->constraints = constraints;
    this->maxlifetime = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
    //std::cout << "Bubble maxlifetime: " << this->maxlifetime << std::endl;
    this->lifetime = 0;
    this->isDead = false;
}


void Bubble::update(float timeElapsed){
    if(isDead) return;

    lifetime += timeElapsed;

    if(this->getPosition().y < 0){
        this->isDead = true;
        //std::cout << "Bubble died" << std::endl;
    }

    float dispY = -yVelocity() * timeElapsed;
    float dispX = xVelocity() * timeElapsed;

    move(dispX, dispY);

}

float Bubble::yVelocity(){
    float rho = 0.1;
    float g = 9.81;
    float A = 3.14*(this->size)*(this->size);
    float Cd = 0.47;
    float m = 1;
    float factor = 200;
    float v = factor * std::sqrt(2 * m * g / (rho * A * Cd)) * std::tanh(lifetime * std::sqrt((rho * A * Cd * g) / (2 * m)));

    //std::cout << "Bubble velocity: " << v << std::endl;

    return v;
}

// Generates random velocity according to a normal distribution
float Bubble::xVelocity(){

    std::random_device rd;
    std::mt19937 gen(rd());

    int i;
    float sample;
    float mean = 0;
    float stddev = 20;

    std::normal_distribution<float> d(mean, stddev);
    sample = d(gen);

    //std::cout << sample << std::endl;

    return sample;
}

void Bubble::collideWith(VisibleObject *target) {};
