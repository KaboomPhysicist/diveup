#pragma once

#include "objects/visible-object.h"
#include <vector>

class Triangle : public VisibleObject {
public:
    Triangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3, const sf::Vector2f& position);

    std::vector<sf::Vector2f> calculateAxes();
    sf::Vector2f projectOntoAxis(const sf::Vector2f& axis);

    sf::Vector2f vertices[3];
    sf::Vector2f position;
};
      