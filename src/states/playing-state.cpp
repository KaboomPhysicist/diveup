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
        bubble_constraints = {0, finishline->getPosition().y + 50 , DiveUp::SCREEN_WIDTH, DiveUp::SCREEN_HEIGHT};

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

    diver1->setOxygen(diver1->getOxygen()-timeElapsed*2*log(_level+2));

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
            Bubbles::GenerateBubble(_bubbleIndex, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, _bubbles, visibleObjectManager);
        }
        _bubbleIndex++;
    }
}

void PlayingState::verifyCliffs(Cliff &cliff){

    sf::Rect<float> cliffBound = cliff.getBoundingRect();

    //verify if cliff is colliding with another cliff    
    for (int j=0; j< _cliffs.size(); j++){
        sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();
        if (cliffBound.intersects(targetBound)){
            std::cout << j << std::endl;
            std::vector<float> _cliffPos;
            float desplacement = ((rand() % 2 == 0) ? 1 : -1)*targetBound.height+100;
            _cliffPos = {cliff.getPosition().x, cliff.getPosition().y-desplacement};

            cliff.setPosition(_cliffPos.at(0), _cliffPos.at(1));
            verifyCliffs(cliff);
}}}

void PlayingState::scaleCliffs(float x, float y, Cliff* cliff){
    cliff->scaleCliff(x, y);
}    

void PlayingState::verifySpace(Cliff &cliff){
// verify if there is space for the diver to pass through the cliffs

    sf::Rect<float> cliffBound = cliff.getBoundingRect();
    
    float diverWidth = 80;

    for (int j=0; j< _cliffs.size(); j++){
        sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();

        if (cliffBound.top>=targetBound.top && cliffBound.top+cliffBound.height<=targetBound.top+targetBound.height
            ||cliffBound.top>=targetBound.top && cliffBound.top+cliffBound.height>=targetBound.top+targetBound.height
            ||targetBound.top>=cliffBound.top && targetBound.top+targetBound.height<=cliffBound.top+cliffBound.height
            ||targetBound.top>=cliffBound.top && targetBound.top+targetBound.height>=cliffBound.top+cliffBound.height){

            if (cliffBound.width+targetBound.width+diverWidth>=DiveUp::SCREEN_WIDTH){

                // resize the cliff to 10% of its original size
                
                scaleCliffs(cliffBound.width-cliffBound.width*0.1, cliffBound.height, &cliff);
                //sf::Rect<float> cliffBound = cliff.getBoundingRect();
                verifySpace(cliff);
                
}}}}


void PlayingState::generateCliffs(std::vector<Cliff*> cliffs,float velocity,int cliffsMax){

    std::cout << "Generating Cliffs" << std::endl;

    int _cliffsMax = cliffsMax;
    for (int i=0; i< _cliffsMax ;i++){
        

        //generate random position for cliffs
        std::random_device rd;
        std::mt19937 gen(rd());

        std::normal_distribution<float> ypos(0, 50);
        std::normal_distribution<float> size(100, 50);

        float direction = (rand() % 2 == 0);
        float altura = ypos(gen);
        
        std::vector<float> _cliffPos= {direction*DiveUp::SCREEN_WIDTH, altura};

        //generate size for cliffs
        int sizex = size(gen)+100;
        int sizey = size(gen)+100;

        //std::cout << "size: " << sizex << " " << sizey << std::endl;


        Cliff *cliff = new Cliff(sizex,sizey,direction,velocity);
        cliff->setPosition(_cliffPos.at(0), _cliffPos.at(1));

        // verify if the cliff does not intersect with another cliff

        if (i > 0){
            verifyCliffs(*cliff); 
            verifySpace(*cliff);}
    

        _cliffs.push_back(cliff);

    }
    //the lowest cliff must be over 500, so let's move all cliffs up
    for (Cliff *i : _cliffs){ i->setPosition(i->getPosition().x, i->getPosition().y-500); }

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

    _cliffs = {};

    generateCliffs(_cliffs, _ascendingSpeed, 10);
    _bubbleMax = 15;
    _bubbles = std::vector<Bubble*>(_bubbleMax);


    SCREEN_RANGE = {0, DiveUp::SCREEN_WIDTH, 0, DiveUp::SCREEN_HEIGHT};
    bubble_constraints = {0, -DiveUp::SCREEN_HEIGHT, DiveUp::SCREEN_WIDTH, 2*DiveUp::SCREEN_HEIGHT};

    Bubbles::initBubbles(_bubbleMax, 30, _ascendingSpeed, bubble_constraints, SCREEN_RANGE, this->_bubbles, visibleObjectManager);


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

    sf::Rect<float> lastCliffBound = _cliffs.at(_cliffs.size()-1)->getBoundingRect();
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
