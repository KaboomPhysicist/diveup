# pragma once
#include "../visible-object.h"

class Field: public VisibleObject {
public:
    Field();
    void update(float timeElapsed) override;
};