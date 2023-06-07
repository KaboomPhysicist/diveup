#pragma once
#include <SFML/Audio.hpp>

class Musicmanager  {
    public:
        Musicmanager();
        void startMusic();
        void stopMusic();
        void selectMusic();
        sf::Music music;
};