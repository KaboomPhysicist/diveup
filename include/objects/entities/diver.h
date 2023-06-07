# pragma once

#include "objects/visible-object.h"

class Diver : public VisibleObject {
    public:
        Diver(float constraintLeft, float constraintRight);
        void handleInput(sf::Event *event) override;
        void update(float timeElapsed) override;
        void collideWith(VisibleObject *target) override;

        void Set_texture(std::string textureFilename);
        void setFinishing(bool);

        float getOxygen();
        void setOxygen(float);

        std::vector<sf::Vector2f> calculateAxes();
        sf::Vector2f projectOntoAxis(const sf::Vector2f& axis);
        

    private:
        enum Direction {Left, Right , Down, Up, NONE};
        Direction _direction = NONE;
        float _speed = 100.0f;
        float _constraintLeft;
        float _constraintRight;
        bool _finishing;
        float _oxygen;
        float y_velocity;
};