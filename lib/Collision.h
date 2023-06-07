#pragma once

#include "objects/visible-object.h"
#include "objects/entities/cliff.h"
#include "objects/entities/triangle.h"
#include "objects/entities/diver.h"

namespace colision{
    bool checkCollision(VisibleObject*, VisibleObject*);
}