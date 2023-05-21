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

    ExitButton *exitButton = new ExitButton();
    exitButton->setPosition(95, 460);
    exitButton->setPriority(1);

    initBubbles();

    visibleObjectManager.add("splashscreen", splashscreen);
    visibleObjectManager.add("newGameButton", newGameButton);
    visibleObjectManager.add("exitButton", exitButton);
}

void SplashscreenState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void SplashscreenState::update(float timeElapsed) { 
    BubblesEffect();
    visibleObjectManager.updateAll(timeElapsed);
}

void SplashscreenState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

SplashscreenState::~SplashscreenState() { }

void SplashscreenState::initBubbles(){
    _bubbleCounter = 0;
    _bubbleIndex = 0;
    _bubbleMax = 4;
    _bubbles = std::vector<Bubble*>(_bubbleMax);

    for(int i=0; i<_bubbleMax; i++){
        GenerateBubble(i);
    }

    std::cout << "Bubbles initialized" << std::endl;
}

void SplashscreenState::GenerateBubble(short int index){
    // Generate random position for bubble
    int x = rand() % DiveUp::SCREEN_WIDTH;
    int y = rand() % (DiveUp::SCREEN_HEIGHT - 200) + 200;

    //std::cout << "Bubble index: " << index << std::endl;

    _bubbles.at(index) = new Bubble(sf::Rect<float>(0, 0, DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT));

    _bubbles.at(index)->setPosition(x, y);
    _bubbles.at(index)->setPriority(1);

    std::ostringstream bubbleName;
    bubbleName << "bubble" << index;
    //std::cout << "Created Bubble name: " << bubbleName.str() << std::endl;

    visibleObjectManager.add(bubbleName.str(), _bubbles.at(index));
}

void SplashscreenState::BubblesEffect(){

    //if(_bubbleCounter < _bubbleMax) GenerateBubble(_bubbleIndex);

    _bubbleIndex = 0;

    for(Bubble* bubble : _bubbles){
        if(bubble->isDead){
            visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
            GenerateBubble(_bubbleIndex);
        }
        _bubbleIndex++;
    }
}