#include "states/playing-state.h"
#include "diveup.h"

void PlayingState::init() {

    Field *field = new Field();
    diver *diver1 = new diver(0,400);
    //Cliff *cliff1 = new Cliff();

    diver1->setPosition(100, 200);
    //cliff1->setPosition(0, 200);
    
    field->setPriority(0);
    //cliff1->setPriority(1);
    diver1->setPriority(2);

    _bubbleMax = 15;
    _bubbles = std::vector<Bubble*>(_bubbleMax);

    std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
    Bubbles::initBubbles(_bubbleMax, 30, SCREEN_RANGE, this->_bubbles, visibleObjectManager);

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
    //visibleObjectManager.add("cliff1", cliff1);
 }

void PlayingState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void PlayingState::update(float timeElapsed) { 
    BubblePopulation();
    visibleObjectManager.updateAll(timeElapsed);
}

void PlayingState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

void PlayingState::BubblePopulation(){
        short int _bubbleIndex = 0;
        std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
        for(Bubble* bubble : _bubbles){
            if(bubble->isDead){
                visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
                Bubbles::GenerateBubble(_bubbleIndex, 30, SCREEN_RANGE, _bubbles, visibleObjectManager);
            }
            _bubbleIndex++;
        }
}

void PlayingState::verifyCliffPos(int x, int y){
    // verify if the cliff is not in the same positions as any other cliff

    for (int i = 0; i < _cliffs.size(); i++){
        if (x == _cliffs.at(i)->getPosition().x && y == _cliffs.at(i)->getPosition().y){
            x = rand() % DiveUp::SCREEN_WIDTH;
            y = rand() % (DiveUp::SCREEN_HEIGHT - 1200) + 1200;
            verifyCliffPos(x,y);
        }
    }
}
void PlayingState::generateCliffs(std::vector<Cliff*> cliffs){

    _cliffsMax = 6;
    for (int i=0; i< _cliffsMax ;i++){

        // generate postions
        int x = rand() % DiveUp::SCREEN_WIDTH;
        int y = rand() % (DiveUp::SCREEN_HEIGHT - 1200) + 1200;

        //generate size for cliffs
        int sizex = rand() % 100 + rand() % 100+50;
        int sizey = rand() % 100 + rand() % 100+50;

        std::cout << "sise x: " << sizex << std::endl;
        std::cout << "sise y: " << sizey << std::endl;

        // verify if the cliff is not in the same position as the previous one
        if (i > 0){verifyCliffPos(x,y);}

        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;

        Cliff *cliff = new Cliff(sizey,sizex);
        cliff->setPosition(x, y);
        _cliffs.push_back(cliff);

    }
}

PlayingState::~PlayingState() { }