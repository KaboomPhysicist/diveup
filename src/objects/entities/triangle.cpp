#include "objects/entities/triangle.h"
#include <iostream>
#include <cmath>


Triangle::Triangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;
}

    // Calculate the axes perpendicular to each edge
std::vector<sf::Vector2f> Triangle::calculateAxes() {
    std::vector<sf::Vector2f> axes;

    for (int i = 0; i < 3; i++) {
        sf::Vector2f edge = vertices[(i + 1) % 3] - vertices[i];
        float norm = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        sf::Vector2f axis(-edge.y, edge.x);  // Perpendicular axis
        axes.push_back(axis);
    }

    return axes;
}

    // Project the triangle vertices onto the axis
sf::Vector2f Triangle::projectOntoAxis(const sf::Vector2f& axis) {
    float minProjection = std::numeric_limits<float>::max();
    float maxProjection = -std::numeric_limits<float>::max();


    for (int i = 0; i < 3; i++) {
        //std::cout << "Vertices: " << vertices[i].x << " " << vertices[i].y << std::endl;
        float projection = axis.x * (vertices[i].x) + axis.y * (vertices[i].y);
        minProjection = std::min(minProjection, projection);
        maxProjection = std::max(maxProjection, projection);
    }

    //std::cout << "min: " << minProjection << " max: " << maxProjection << std::endl;

    return sf::Vector2f(minProjection, maxProjection);
}


