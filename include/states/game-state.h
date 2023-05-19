#pragma once

#include <SFML/Graphics.hpp>

class GameState {
public:
    virtual ~GameState();
    virtual void init();
    virtual void handleInput(sf::Event *event);
    virtual void update(float timeElapsed);
    virtual void draw(sf::RenderWindow *window);

protected:
};

