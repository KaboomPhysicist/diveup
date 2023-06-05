#include "states/debug-state.h"
#include "diveup.h"
#include "collision.h"

void DebugState::init() {
    // Initialize the level to 0 and declare a new level.

    Field *field = new Field();
    diver1 = new Diver(0,400);

    diver1->setFinishing(false);
    diver1->setPosition(100, 600);

    sf::Rect<float> diverBound = diver1->getBoundingRect();

    field->setPriority(0);
    diver1->setPriority(2);

    //generate random position for cliffs
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<float> ypos(0, 10);
    std::normal_distribution<float> size(100, 50);

    float direction = (rand() % 2 == 0);
    float altura = ypos(gen);
    
    std::vector<float> _cliffPos= {direction*DiveUp::SCREEN_WIDTH/2, DiveUp::SCREEN_HEIGHT/2};

    //generate size for cliffs
    int sizex = size(gen)+100;
    int sizey = size(gen)+100;

    //std::cout << "size: " << sizex << " " << sizey << std::endl;


    cliff = new Cliff(200, 200, direction, 0);
    cliff->setPosition(_cliffPos.at(0), _cliffPos.at(1));


    visibleObjectManager.add("cliff", cliff);
    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
}

void DebugState::handleInput(sf::Event *event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Escape) {
            // If the escape key is pressed, go back to the menu.
            DiveUp::setState(DiveUp::State::Splashscreen);
        }
    }

    if (event->type == sf::Event::MouseButtonPressed) {
        int x = event->mouseButton.x;
        int y = event->mouseButton.y;

        sf::Vector2f mousePosition = sf::Vector2f(x, y);

    if(Collision::singlePixelTest(cliff->getSprite(), mousePosition, 0)) std::cout << "Clicked!"  << std::endl;

}
    visibleObjectManager.handleInputAll(event);
}

void DebugState::update(float timeElapsed) {
    // Update the level.
    
    visibleObjectManager.updateAll(timeElapsed);
}

void DebugState::draw(sf::RenderWindow *window) {
    // Draw the level.
    visibleObjectManager.drawAll(window);
}

DebugState::~DebugState() {
}

