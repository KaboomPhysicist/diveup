# pragma once

#include "objects/visible-object.h"
#include "objects/entities/bubble.h"

class Diver : public VisibleObject {
    public:
        Diver(float constraintLeft, float constraintRight);
        void handleInput(sf::Event *event);
        void update(float timeElapsed);
        void collideWith(VisibleObject *target);

        void Set_texture(std::string textureFilename);
        void setFinishing(bool);


    private:
        enum Direction { Left, Right ,NONE};

        Direction _direction = NONE;
        float _speed = 100.0f;
        float _constraintLeft;
        float _constraintRight;
        float _oxygen;
        bool _finishing;
        float y_velocity;


};