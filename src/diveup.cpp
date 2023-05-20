# include "diveup.h"

sf::RenderWindow DiveUp::_window;
sf::Clock DiveUp::_clock;
DiveUp::State DiveUp::_state = Uninitialized;
std::map<DiveUp::State, GameState*> DiveUp::_stateInstances;
GameState *DiveUp::_currentState;

void DiveUp::start()
{
    if (_state != Uninitialized) return;

    // Create the game window
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "DiveUp");
    // Set max framerate
    _window.setFramerateLimit(60);

    // Initialize the _stateInstances map with all the [non-utilitary] game states
    _stateInstances[Splashscreen] = new SplashscreenState();
    _stateInstances[Splashscreen]->init();
    _stateInstances[Playing] = new PlayingState();
    _stateInstances[Playing]->init();
    _stateInstances[Gameover] = new gameoverState();
    _stateInstances[Gameover]->init();

    // Set the initial state in Splashscreen
    _state = Splashscreen;

    gameLoop();

    // Free the memory allocated for the game states after the game loop ends
    auto itr = _stateInstances.begin();
    while (itr != _stateInstances.end()) {
        delete itr->second;
        itr++;
    }

    _window.close();
}

void DiveUp::gameLoop() {
    while (_state != Exiting) {
        float timeElapsed = _clock.restart().asSeconds();
        _window.clear(sf::Color(255, 255, 255));

        // We operate over the state that enters initially to the loop
        _currentState = _stateInstances[_state];

        // Handle input
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { _state = Exiting; }
            _currentState->handleInput(&event);
        }

        // Update our entities
        _currentState->update(timeElapsed);

        // Draw our new entities
        _currentState->draw(&_window);

        _window.display();

        //_currentState->endLoopLogic();
    }
}

void DiveUp::setState(DiveUp::State s) {
    _state = s;
}

GameState *DiveUp::getState() {
    return _currentState;
}

