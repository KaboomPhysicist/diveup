#include "states/splashscreen-state.h"
#include "diveup.h"
#include <sstream>

void SplashscreenState::init() { 
    // Add the backgroud
    SplashScreen *splashscreen = new SplashScreen();
    splashscreen->setPriority(0);

    // Add the buttons of the splashscreen/menu
    NewGameButton *newGameButton = new NewGameButton();
    newGameButton->setPosition(95, 360);
    newGameButton->setPriority(1);

    ExitButton *exitButton = new ExitButton(sf::Vector2f(300,80));
    exitButton->setPosition(95, 460);
    exitButton->setPriority(1);

    _bubbleMax = 5;
    _bubbles = std::vector<Bubble*>(_bubbleMax);
    SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 200, DiveUp::SCREEN_HEIGHT - 100};
    bubble_constraints = {0, -20, DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT+20};

    Bubble::initBubbles(_bubbleMax, 200, 0, bubble_constraints, SCREEN_RANGE,_bubbles, visibleObjectManager);

    visibleObjectManager.add("splashscreen", splashscreen);
    visibleObjectManager.add("newGameButton", newGameButton);
    visibleObjectManager.add("exitButton", exitButton);
    std::cout << "Splashscreen initialized" << std::endl;

   /* if (!music.openFromFile("/home/laura/Documents/Universidad/Semestre 9/Física computacional II/Proyecto-final/diveup/assets/sound(1).wav"))
        std::cout << "Error loading music" << std::endl;
    music.play();
    music.setLoop(true);*/

}/*
void SplashscreenState::stopMusic(){
    music.stop();
}
void SplashscreenState::startMusic(){
    music.play();
}
*/
void SplashscreenState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void SplashscreenState::update(float timeElapsed) { 
    //if (!dynamic_cast<SplashscreenState*>(DiveUp::getState())){music.stop();}
    BubblesEffect();
    visibleObjectManager.updateAll(timeElapsed);
}

void SplashscreenState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

SplashscreenState::~SplashscreenState() { }

void SplashscreenState::BubblesEffect(){

    //if(_bubbleCounter < _bubbleMax) GenerateBubble(_bubbleIndex);

    short int _bubbleIndex = 0;

    for(Bubble* bubble : _bubbles){
        if(bubble->isDead){
            visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
            Bubble::GenerateBubble(_bubbleIndex, 200, 0, bubble_constraints, SCREEN_RANGE, _bubbles, visibleObjectManager);
        }
        _bubbleIndex++;
    }
}