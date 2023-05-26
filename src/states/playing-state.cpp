#include "states/playing-state.h"
#include "diveup.h"

void PlayingState::init() {
    _level = 0;
    initAirmarker(50,50);
    newLevel();
}

void PlayingState::handleInput(sf::Event *event) {
    visibleObjectManager.handleInputAll(event);
}

void PlayingState::update(float timeElapsed) { 
  
    if(_end) reset(); 

    if(finishline->getPosition().y > -DiveUp::SCREEN_HEIGHT){
        if(finishline->getPosition().y < 0){
        SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, static_cast<int>(finishline->getPosition().y), 0};
        }
        else{
        //std::cout << "Visible" << std::endl;
        SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT, DiveUp::SCREEN_HEIGHT};
        }
        bubble_constraints = {0, finishline->getPosition().y + 5 , DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT};

    }

    BubblePopulation();

    if (finishline->getPosition().y > 200){
        _ascendingSpeed = 0;
        for(Bubble* bubble : _bubbles){
            bubble->setBias(0);
        }
        finishline->setFinishing(true);
        diver1->setFinishing(true);
    } 

    opacityupdate(diver1->getOxygen());

    visibleObjectManager.updateAll(timeElapsed);
}

void PlayingState::reset(){
    //std::cout << "Reseting..." << std::endl;
    visibleObjectManager.remove("diver1");
    visibleObjectManager.remove("finishline");

    for (int i = 0; i < _cliffs.size(); i++){
        visibleObjectManager.remove("cliff" + std::to_string(i));
    }

    for (int i=0; i < _bubbles.size(); i++){
        visibleObjectManager.remove("bubble" + std::to_string(i));

    }

    _level++;
    setEnded(false);
    newLevel();
}

void PlayingState::draw(sf::RenderWindow *window) { 
    visibleObjectManager.drawAll(window);
}

void PlayingState::BubblePopulation(){
    short int _bubbleIndex = 0;

    for(Bubble* bubble : _bubbles){
        if(bubble->isDead){
            visibleObjectManager.remove("bubble" + std::to_string(_bubbleIndex));
            Bubble::GenerateBubble(_bubbleIndex, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, _bubbles, visibleObjectManager);
        }
        _bubbleIndex++;
    }
}


void PlayingState::initAirmarker(int x,int y ){
    //generate air markers
    
    float position = 10;
    for (int i=0; i< 5 ;i++){
        AirCounter *airmarker = new AirCounter(x,y);
        sf::Rect<float> aircounterbound = airmarker->getBoundingRect();
        
        airmarker->setPosition(position, 20);
        position += aircounterbound.width;
        airmarker->setPriority(2);
        _aircounters.push_back(airmarker);

    }   
} 

void PlayingState::opacityupdate(int oxigenoquememuero){
    //update opacity of air markers
    //std::cout<<"oxigenoquememuero" << oxigenoquememuero << std::endl;

switch (oxigenoquememuero) {
    case 81 ... 100:
        _aircounters.at(4)->setOpacity(100 - oxigenoquememuero);
        _aircounters.at(3)->setOpacity(20);
        _aircounters.at(2)->setOpacity(20);
        _aircounters.at(1)->setOpacity(20);
        _aircounters.at(0)->setOpacity(20);
        break;
    case 61 ... 80:
        _aircounters.at(4)->setOpacity(0);
        _aircounters.at(3)->setOpacity(80 - oxigenoquememuero);
        _aircounters.at(2)->setOpacity(20);
        _aircounters.at(1)->setOpacity(20);
        _aircounters.at(0)->setOpacity(20);
        break;
    case 41 ... 60:
        _aircounters.at(4)->setOpacity(0);
        _aircounters.at(3)->setOpacity(0);
        _aircounters.at(2)->setOpacity(60 - oxigenoquememuero);
        _aircounters.at(1)->setOpacity(20);
        _aircounters.at(0)->setOpacity(20);
        break;
    case 21 ... 40:
        _aircounters.at(4)->setOpacity(0);
        _aircounters.at(3)->setOpacity(0);
        _aircounters.at(2)->setOpacity(0);
        _aircounters.at(1)->setOpacity(40 - oxigenoquememuero);
        _aircounters.at(0)->setOpacity(20);
        break;
    case 1 ... 20:
        _aircounters.at(4)->setOpacity(0);
        _aircounters.at(3)->setOpacity(0);
        _aircounters.at(2)->setOpacity(0);
        _aircounters.at(1)->setOpacity(0);
        _aircounters.at(0)->setOpacity(20 - oxigenoquememuero);
        break;
    case 0:
    std::cout << "Muerte por asfixia" << std::endl;
    setEnded(true);
    resetLevel();
    DiveUp::setState(DiveUp::Gameover);
}
}

void PlayingState::newLevel(){

    std::cout << "Generando nuevo nivel" << std::endl;

    Field *field = new Field();
    diver1 = new Diver(0,400);

    diver1->setFinishing(false);
    diver1->setPosition(100, 600);

    sf::Rect<float> diverBound = diver1->getBoundingRect();
    std::cout<<"diver width: "<< diverBound.width << std::endl;

    
    field->setPriority(0);
    diver1->setPriority(2);

    _ascendingSpeed = 200 * std::log(_level + 2);

    int cliff_number = 10 + _level * 5;
    _cliffs = {};

    Cliff::generateCliffs(_cliffs, _ascendingSpeed, cliff_number);

    _bubbleMax = 10;
    _bubbles = std::vector<Bubble*>(_bubbleMax);

    SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
    bubble_constraints = {0, -DiveUp::SCREEN_HEIGHT, DiveUp::SCREEN_WIDTH, 2*DiveUp::SCREEN_HEIGHT};

    Bubble::initBubbles(_bubbleMax, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, this->_bubbles, visibleObjectManager);


    float finishPosition = 0;

    for (int i = 0; i < _cliffs.size(); i++){
        if(finishPosition > _cliffs.at(i)->getBoundingRect().top){
            finishPosition = _cliffs.at(i)->getBoundingRect().top;
        }

        visibleObjectManager.add("cliff" + std::to_string(i), _cliffs.at(i));
        _cliffs.at(i)->setPriority(1);
    }

    for (int i = 0; i < _aircounters.size(); i++){
        visibleObjectManager.add("aircounter" + std::to_string(i), _aircounters.at(i));
        _aircounters.at(i)->setPriority(2);
    }
    SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, -DiveUp::SCREEN_HEIGHT, 0};

    // Generate EndLine based on the top position of the last cliff

    //sf::Rect<float> lastCliffBound = _cliffs.at(_cliffs.size()-1)->getBoundingRect();
    finishPosition = finishPosition - 800;
    //float finishPosition = 200;

    finishline = new FinishLine(finishPosition, _ascendingSpeed);
    finishline->setPriority(1);
    finishline->setFinishing(false);

    visibleObjectManager.add("field", field);
    visibleObjectManager.add("diver1", diver1);
    visibleObjectManager.add("finishline", finishline);
}

void PlayingState::setEnded(bool end){
  _end = end;
}

void PlayingState::resetLevel(){
    _level = -1;
}

PlayingState::~PlayingState() { }
