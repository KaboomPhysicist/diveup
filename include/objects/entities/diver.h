# pragma once

#include "objects/visible-object.h"

class diver : public VisibleObject {
    public:
        diver(float constraintLeft, float constraintRight);
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
        //void collideWith(VisibleObject *target);

        void Set_texture(std::string textureFilename);

    private:
        enum Direction { Left, Right ,NONE};

        Direction _direction = NONE;
        float _speed = 100.0f;
        float _constraintLeft;
        float _constraintRight;


};