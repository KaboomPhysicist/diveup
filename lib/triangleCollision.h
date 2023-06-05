#pragma once

#include "objects/visible-object.h"
#include "objects/entities/triangle.h"

namespace colision{
    bool checkCollision(const VisibleObject&, const VisibleObject&);
}