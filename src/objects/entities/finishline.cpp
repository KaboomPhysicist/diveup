#include "objects/entities/finishline.h"
#include "diveup.h"
#include "states/playing-state.h"

FinishLine::FinishLine(int position, float speed) : VisibleObject("assets/finishline.png") {
    this->setPosition(0, position);
    velocity = speed;
}

void FinishLine::collideWith(VisibleObject *target) {
    if(!dynamic_cast<Diver*>(target) ) return;
    //std::cout << "Llegaste a la meta" << std::endl;
    dynamic_cast<PlayingState*>(DiveUp::getState())->setEnded(true);
    DiveUp::setState(DiveUp::NextLevel);
};

void FinishLine::update(float timeElapsed) {
    //std::cout << "Line position:" << this->getPosition().y << std::endl;
    if(_finishing){
        this->move(0, 0);
    }
    else{
        this->move(0, velocity * timeElapsed);
    }
}

void FinishLine::handleInput(sf::Event *event) {
}

void FinishLine::setFinishing(bool val){
    _finishing = val;
}
