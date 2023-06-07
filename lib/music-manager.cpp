#include "music-manager.h"
#include "diveup.h"

Musicmanager::Musicmanager(){
    if (!music.openFromFile("assets/splashscreen1.wav"))
        {std::cout << "Error loading music" << std::endl;}
        //std::cout << "Splashscreen music" << std::endl;
};

void Musicmanager::startMusic()
{
    music.setVolume(35.f);
    music.play();
}
void Musicmanager::stopMusic()
{
    music.stop();
}

void Musicmanager::selectMusic()
{

    if (dynamic_cast<SplashscreenState *>(DiveUp::getState()))
    {    if (!music.openFromFile("assets/splashscreen1.wav"))
                {std::cout << "Error loading music" << std::endl;}
            //std::cout << "Splashscreen music" << std::endl;
            }
    else if (dynamic_cast<PlayingState *>(DiveUp::getState()))
    {    if (!music.openFromFile("assets/playingstate.wav"))
                std::cout << "Error loading music" << std::endl;
                //std::cout << "Playing music" << std::endl;
                }
    else if (dynamic_cast<gameoverState *>(DiveUp::getState()))
    {    if (!music.openFromFile("assets/gameover.wav"))
                std::cout << "Error loading music" << std::endl;
                    //std::cout << "Gameover music" << std::endl;
                    }
    else if (dynamic_cast<NextLevelState*>(DiveUp::getState()))
    {    if (!music.openFromFile("assets/splashscreen1.wav"))
                std::cout << "Error loading music" << std::endl;
                //std::cout << "NextLevel music" << std::endl;
                }
}