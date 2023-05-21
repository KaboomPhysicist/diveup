#include "states/splashscreen-state.h"
#include "diveup.h"

void SplashscreenState::init() { 
    // Add the backgroud
    SplashScreen *splashscreen = new SplashScreen();
    splashscreen->setPriority(0);

    // Add the buttons of the splashscreen/menu
    NewGameButton *newGameButton = new NewGameButton();
    newGameButton->setPosition(120, 400);
    newGameButton->setPriority(1);

    ExitButton *exitButton = new ExitButton();
    exitButton->setPosition(120, 450);
    exitButton->setPriority(1);

    

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

void SplashscreenState::BubblesEffect(){
    // Generate random position for bubble
    int x = rand() % DiveUp::SCREEN_WIDTH;
    int y = rand() % DiveUp::SCREEN_HEIGHT;

    Bubble *bubble = new Bubble(sf::Rect<float>(0, 0, DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT));
    bubble->setPosition(x, y);
    bubble->setPriority(1);
    visibleObjectManager.add("testbubble", bubble);
    
    if(bubble->isDead){
        visibleObjectManager.remove("testbubble");
    }
}