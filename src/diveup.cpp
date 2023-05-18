# include "diveup.h"

sf::RenderWindow DiveUp::_window;
sf::Clock DiveUp::_clock;

void DiveUp::start()
{
    if (_window.isOpen()) return;

    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32), "DiveUp");
    _window.setFramerateLimit(60);

    gameLoop();
}

void DiveUp::gameLoop()
{
    while (_window.isOpen())
    {
        float timeElapsed = _clock.restart().asSeconds();
        _window.clear(sf::Color(255, 255, 255));

        
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        
        _window.display();
    }
}
