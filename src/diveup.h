# pragma once

#include <SFML/Graphics.hpp>

class DiveUp
{
    public:
        const static int SCREEN_WIDTH = 2048;
        const static int SCREEN_HEIGHT = 1536;
        static void start();
        static void gameLoop();
    private:
      static sf::RenderWindow _window;
      static sf::Clock _clock;
};