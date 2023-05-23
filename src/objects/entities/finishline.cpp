#include "objects/entities/finishline.h"
#include "diveup.h"

FinishLine::FinishLine(int position) : VisibleObject("assets/finishline.png") {
    this->position = position;
    velocity = 50.0f;
}

void FinishLine::collideWith(VisibleObject *target) {
    if(!dynamic_cast<Diver*>(target) ) return;
    std::cout << "Llegaste a la meta" << std::endl;
    DiveUp::setState(DiveUp::NextLevel);
};