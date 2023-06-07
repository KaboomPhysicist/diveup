# pragma once

#include <SFML/Graphics.hpp>
#include "states/game-state.h"
#include "states/splashscreen-state.h"
#include "states/playing-state.h"
#include "states/gameover-state.h"
#include "states/nextlevel-state.h"
#include "states/debug-state.h"
# include "music-manager.h"

class DiveUp
{
    public:
        const static int SCREEN_WIDTH = 480;
        const static int SCREEN_HEIGHT = 720;
        static void start();
        static void gameLoop();

        enum State {Uninitialized, Splashscreen, Playing, NextLevel, Gameover, Exiting, Debugging};
        static void setState(State s);
        static GameState *getState();
        static Musicmanager musicmanager;

    private:
        static State _state;
        static GameState *_currentState;
        static GameState* _currentstatemusic;
        static std::map<State, GameState*> _stateInstances;
        static sf::RenderWindow _window;
        static sf::Clock _clock;

};