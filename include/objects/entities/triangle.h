#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Triangle {
public:
    Triangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3);

    std::vector<sf::Vector2f> calculateAxes();
    sf::Vector2f projectOntoAxis(const sf::Vector2f& axis);

    sf::Vector2f vertices[3];
};
      