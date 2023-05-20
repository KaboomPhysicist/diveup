#pragma once

#include <SFML/Graphics.hpp>
#include "objects/visible-object-manager.h"

class GameState {
public:
    virtual ~GameState();
    virtual void init();
    virtual void handleInput(sf::Event*);
    virtual void update(float);
    virtual void draw(sf::RenderWindow*);
    virtual void endLoopLogic() {};

    VisibleObjectManager* getObjectManager();

protected:
    VisibleObjectManager visibleObjectManager;
};

