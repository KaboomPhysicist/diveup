#include "Collision.h"
#include <vector>

// Function to check for collision between visible objects
namespace colision{
    bool checkCollision(VisibleObject* origin, VisibleObject* target) {

        //VisibleObject can be Cliff, Bubble or Diver
        // Cliffs have a triangle linked for the collision detection with the diver
        // Cliffs can also collide with bubbles (not a great priority)

        // Check if one object is a Cliff and the other is a diver
        if((dynamic_cast<Cliff*>(origin) && dynamic_cast<Diver*>(target)) || 
            (dynamic_cast<Cliff*>(origin) && dynamic_cast<Diver*>(target))){
                
                //std::cout << "Cliff and Diver" << std::endl;

                // Assign the corresponding variable

                Cliff* cliff = (dynamic_cast<Cliff*>(origin)) ? dynamic_cast<Cliff*>(origin) : dynamic_cast<Cliff*>(target);
                Diver* diver = (dynamic_cast<Diver*>(origin)) ? dynamic_cast<Diver*>(origin) : dynamic_cast<Diver*>(target);

                // Get the triangle from the cliff
                Triangle *triangle = cliff->getTriangle();

                std::vector<sf::Vector2f> axes;
                axes.reserve(5);

                // Calculate axes for triangle and diver
                std::vector<sf::Vector2f> axestriangle = triangle->calculateAxes();
                std::vector<sf::Vector2f> axes2 = diver->calculateAxes();


                axes.insert(axes.end(), axestriangle.begin(), axestriangle.end());
                axes.insert(axes.end(), axes2.begin(), axes2.end());

                // Project and check for overlap on each axis
                for (const auto& axis : axes) {
                    sf::Vector2f projection1 = triangle->projectOntoAxis(axis);
                    sf::Vector2f projection2 = diver->projectOntoAxis(axis);

                    if (projection1.y < projection2.x || projection2.y < projection1.x) {
                        // No overlap found on this axis, triangles are not colliding
                        return false;
                    }
        }

        // Overlap found on all axes, triangles are colliding
        return true;
            }
        // All the other collisions can be handled with pixelPerfectTest from the library
        else if (Collision::pixelPerfectTest(origin->getSprite(), target->getSprite())) {
          return true;

        }
        return false;
    }
}