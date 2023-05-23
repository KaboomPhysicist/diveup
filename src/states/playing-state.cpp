#include "states/playing-state.h"
#include "diveup.h"

void PlayingState::init() {
    newLevel();
    
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

        //verify if cliff is colliding with another cliff    
        for (int j=0; j< _cliffs.size(); j++){
        
            sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();
            if (cliffBound.intersects(targetBound)) {

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
    // verifys if there is space for the diver to pass through the cliffs

        sf::Rect<float> cliffBound = cliff.getBoundingRect();
        
        float diverWidth = 80;

        for (int j=0; j< _cliffs.size(); j++){
            sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();
            if (cliffBound.top<=targetBound.top && cliffBound.top>=targetBound.top-targetBound.height){

                if (cliffBound.width+targetBound.width+diverWidth>=DiveUp::SCREEN_WIDTH){

                    std::cout << "cliff width antes rescale: " << cliffBound.width << std::endl;
                   // cliff.scale(cliffBound.width-cliffBound.width*0.15, cliffBound.height);
                    scaleCliffs(cliffBound.width-cliffBound.width*0.15, cliffBound.height, &cliff);
                    std::cout << "cliff width depois rescale: " << cliffBound.width << std::endl;
                    verifySpace(cliff);
                   
}}}}


void PlayingState::generateCliffs(std::vector<Cliff*> cliffs){

    _cliffsMax = 30;
    for (int i=0; i< _cliffsMax ;i++){
        

        //generate random position for cliffs
        std::random_device rd;
        std::mt19937 gen(rd());

        std::normal_distribution<float> ypos(0, 50);
        std::normal_distribution<float> size(100, 50);

        float direction = (rand() % 2 == 0);
        float altura = ypos(gen);
        
        std::vector<float> _cliffPos= {direction*DiveUp::SCREEN_WIDTH,altura};

        //generate size for cliffs
        int sizex = size(gen)+100;
        int sizey = size(gen)+100;

        //std::cout << "size: " << sizex << " " << sizey << std::endl;

        Cliff *cliff = new Cliff(sizex,sizey,direction);
        cliff->setPosition(_cliffPos.at(0), _cliffPos.at(1));

        // verify if the cliff does not intersect with another cliff

        if (i > 0){
            verifyCliffs(*cliff); 
            verifySpace(*cliff);}
    

        _cliffs.push_back(cliff);

    }
}

void PlayingState::newLevel(){
    Field *field = new Field();
    Diver *diver1 = new Diver(0,400);

    diver1->setPosition(100, 550);
    sf::Rect<float> diverBound = diver1->getBoundingRect();
    std::cout<<"diver width: "<<diverBound.width<<std::endl;

    
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

PlayingState::~PlayingState() { }