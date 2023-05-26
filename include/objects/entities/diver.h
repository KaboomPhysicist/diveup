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

        float getOxygen();
        void setOxygen(float);
        

    private:
        enum Direction { Left, Right ,NONE};
        Direction _direction = NONE;
        float _speed = 100.0f;
        float _constraintLeft;
        float _constraintRight;
        bool _finishing;
        float _oxygen;
        float y_velocity;
};