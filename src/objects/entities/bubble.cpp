#include "objects/entities/bubble.h"
#include <cmath>
#include <random>
#include <sstream>

Bubble::Bubble(sf::Rect<float> constraints, float factor, float velocity_bias = 0) : VisibleObject("assets/bubble1.png") {
    // Apply transparency to the sprite. Last value is the alpha value.
    //this->_sprite.setColor(sf::Color(255, 255, 255, 128));

    this->size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5)) + 22;

    sf::Vector2f targetSize(this->size, this->size); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height);

    this->velocity_factor = factor;
    this->velocity_bias = velocity_bias;
    this->constraints = constraints;

    this->maxlifetime = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
    //std::cout << "Bubble maxlifetime: " << this->maxlifetime << std::endl;
    this->lifetime = 0;
    this->isDead = false;
}


void Bubble::update(float timeElapsed){
    if(isDead) return;

    lifetime += timeElapsed;

    //Check for constraints
    if(getTop()<constraints.top || getBottom() > (constraints.top + constraints.height) || getLeft() < constraints.left || getRight() > (constraints.left + constraints.width)){
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
    float v = velocity_factor * std::sqrt(2 * m * g / (rho * A * Cd)) * std::tanh(lifetime * std::sqrt((rho * A * Cd * g) / (2 * m))) - velocity_bias;

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

void Bubble::collideWith(VisibleObject *target) {
    if(!dynamic_cast<Diver*>(target) and !dynamic_cast<Cliff*>(target)) return;

    //if(!dynamic_cast<Bubble*>(target)) return;

    this->isDead = true;

};

namespace Bubbles{

    void GenerateBubble(short int index, float velocity_factor, float velocity_bias, sf::Rect<float> constraints, std::vector<int> SCREEN_RANGE, std::vector<Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager){
        // Generate random position for bubble

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> disx(SCREEN_RANGE.at(0), SCREEN_RANGE.at(1));
        std::uniform_int_distribution<> disy(SCREEN_RANGE.at(2), SCREEN_RANGE.at(3));

        //int x = (rand() % SCREEN_RANGE.at(1)) + SCREEN_RANGE.at(0);
        //int y = (rand() % SCREEN_RANGE.at(3)) + SCREEN_RANGE.at(2);

        int x = disx(gen);
        int y = disy(gen);

        //std::cout << "Bubble index: " << index << std::endl;

        //sf::Rect<float> constraints(0, SCREEN_RANGE.at(2), SCREEN_RANGE.at(1), 720);

        _bubbles.at(index) = new Bubble(constraints, velocity_factor, velocity_bias);

        _bubbles.at(index)->setPosition(x, y);
        _bubbles.at(index)->setPriority(1);

        std::ostringstream bubbleName;
        bubbleName << "bubble" << index;
        //std::cout << "Created Bubble name: " << bubbleName.str() << std::endl;

        visibleObjectManager.add(bubbleName.str(), _bubbles.at(index));
    }

    void initBubbles(short int bubbleMax, float velocity_factor, float velocity_bias, sf::Rect<float> constraints, std::vector<int> SCREEN_RANGE, std::vector <Bubble*>& _bubbles, VisibleObjectManager& visibleObjectManager){
        for(int i=0; i<bubbleMax; i++){
            GenerateBubble(i, velocity_factor, velocity_bias, constraints, SCREEN_RANGE, _bubbles, visibleObjectManager);
        }
    }
}
