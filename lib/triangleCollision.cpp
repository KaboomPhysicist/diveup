#include "triangleCollision.h
#include <vector>

// Function to check for collision between visible objects
namespace colision{
bool checkCollision(const VisibleObject& origin, const VisibleObject& target) {


    // Check if both objects are triangles
    const Triangle* triangle1 = dynamic_cast<const Triangle*>(&origin);
    const Triangle* triangle2 = dynamic_cast<const Triangle*>(&target);

    if (triangle1 == nullptr || triangle2 == nullptr) {
        return false;
    }

    std::vector<sf::Vector2f> axes;
    axes.reserve(6);

    // Calculate axes for both triangles
    std::vector<sf::Vector2f> axes1 = triangle1.calculateAxes();
    std::vector<sf::Vector2f> axes2 = triangle2.calculateAxes();

    axes.insert(axes.end(), axes1.begin(), axes1.end());
    axes.insert(axes.end(), axes2.begin(), axes2.end());

    // Project and check for overlap on each axis
    for (const auto& axis : axes) {
        sf::Vector2f projection1 = triangle1.projectOntoAxis(axis);
        sf::Vector2f projection2 = triangle2.projectOntoAxis(axis);

        if (projection1.y < projection2.x || projection2.y < projection1.x) {
            // No overlap found on this axis, triangles are not colliding
            return false;
        }
    }

    // Overlap found on all axes, triangles are colliding
    return true;
}
}