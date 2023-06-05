#include "objects/entities/triangle.h"


Triangle::Triangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3, const sf::Vector2f& position) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;
    this->position = position;
}

    // Calculate the axes perpendicular to each edge
std::vector<sf::Vector2f> Triangle::calculateAxes() {
    std::vector<sf::Vector2f> axes;

    for (int i = 0; i < 3; i++) {
        sf::Vector2f edge = vertices[(i + 1) % 3] - vertices[i];
        sf::Vector2f axis(-edge.y, edge.x);  // Perpendicular axis
        axes.push_back(axis);
    }

    return axes;
}

    // Project the triangle vertices onto the axis
sf::Vector2f Triangle::projectOntoAxis(const sf::Vector2f& axis) {
    float minProjection = std::numeric_limits<float>::max();
    float maxProjection = std::numeric_limits<float>::min();

    for (int i = 0; i < 3; i++) {
        float projection = axis.x * (vertices[i].x + position.x) + axis.y * (vertices[i].y + position.y);
        minProjection = std::min(minProjection, projection);
        maxProjection = std::max(maxProjection, projection);
    }

    return sf::Vector2f(minProjection, maxProjection);
}


