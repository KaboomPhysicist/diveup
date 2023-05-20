# pragma once

#include <SFML/Graphics.hpp>

#include "states/game-state.h"
#include "states/splashscreen-state.h"
#include "states/playing-state.h"
#include "states/gameover-state.h"


class DiveUp
{
    public:
        const static int SCREEN_WIDTH = 480;
        const static int SCREEN_HEIGHT = 720;
        static void start();
        static void gameLoop();

        enum State {Uninitialized, Splashscreen, Playing, Gameover, Exiting};
        static void setState(State s);
        static GameState *getState();

    private:
        static State _state;
        static GameState *_currentState;
        static std::map<State, GameState*> _stateInstances;
        static sf::RenderWindow _window;
        static sf::Clock _clock;

};