#include "states/playing-state.h"
#include "diveup.h"

void PlayingState::init() {

    Field *field = new Field();
    Diver *diver1 = new Diver(0,400);

    diver1->setPosition(100, 200);
    
    field->setPriority(0);
    diver1->setPriority(2);

    generateCliffs(_cliffs);

    _bubbleMax = 15;
    _bubbles = std::vector<Bubble*>(_bubbleMax);

    _ascendingSpeed = 200;

    std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
    bubble_constraints = {0, -DiveUp::SCREEN_HEIGHT, DiveUp::SCREEN_WIDTH, 2*DiveUp::SCREEN_HEIGHT};

    Bubbles::initBubbles(_bubbleMax, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, this->_bubbles, visibleObjectManager);

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);

    for (int i = 0; i < _cliffs.size(); i++){
        visibleObjectManager.add("cliff" + std::to_string(i), _cliffs.at(i));
        _cliffs.at(i)->setPriority(1);
    }
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
        std::vector SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, -DiveUp::SCREEN_HEIGHT, 0};

        for(Bubble* bubble : _bubbles){
            if(bubble->isDead){
                visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
                Bubbles::GenerateBubble(_bubbleIndex, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, _bubbles, visibleObjectManager);
            }
            _bubbleIndex++;
        }
}
void PlayingState::verifyCliffs(Cliff &cliff){

        sf::Rect<float> cliffBound = cliff.getBoundingRect();
        for (int j=0; j< _cliffs.size(); j++){
        
            sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();


            if (cliffBound.intersects(targetBound)) {
                //std::cout << "cliff intersected" << std::endl;

                std::vector<float> _cliffPos;
                float desplacement = ((rand() % 2 == 0) ? 1 : -1)*targetBound.height;

                _cliffPos = {cliff.getPosition().x,
                             cliff.getPosition().y+desplacement};


                cliff.setPosition(_cliffPos.at(0), _cliffPos.at(1));
                
                verifyCliffs(cliff);
                }

                
        }
}


void PlayingState::generateCliffs(std::vector<Cliff*> cliffs){

    _cliffsMax = 5;
    for (int i=0; i< _cliffsMax ;i++){

        //generate random position for cliffs
        std::random_device rd;
        std::mt19937 gen(rd());

        std::normal_distribution<float> ypos(360, 300);
        std::normal_distribution<float> size(200, 50);

        std::vector<float> _cliffPos= {0,ypos(gen)};

        //generate size for cliffs
        int sizex = size(gen)-50;
        int sizey = size(gen);

        Cliff *cliff = new Cliff(sizey,sizex);
        cliff->setPosition(_cliffPos.at(0), _cliffPos.at(1));

        // verify if the cliff is not in the same position as the previous one


        if (i > 0){
            verifyCliffs(*cliff); }

        _cliffs.push_back(cliff);

    }
}


PlayingState::~PlayingState() { }