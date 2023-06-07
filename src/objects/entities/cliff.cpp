#include "objects/entities/cliff.h"
#include "diveup.h"

Cliff::Cliff(int sizex, int sizey,float dir,float speed) : VisibleObject("assets/cliff2.png") { 
    sf::Vector2f targetSize(sizex, sizey); 
    if (dir == 1.0f) {
        this->_sprite.setScale(
                            -targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
    } else {
        this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
    }
    
    velocity = speed;
}


void Cliff::collideWith(VisibleObject *target) {
    if(!dynamic_cast<Diver*>(target) ) return;
    
    std::cout << "Te diste un tiestaso" << std::endl;
    
    // Check if State is PlayingState
    if(!dynamic_cast<PlayingState*>(DiveUp::getState())) return;

    dynamic_cast<PlayingState*>(DiveUp::getState())->setEnded(true);
    dynamic_cast<PlayingState*>(DiveUp::getState())->resetLevel();

    DiveUp::setState(DiveUp::Gameover);
        
};


void Cliff::update(float timeElapsed) { 

    move(0, velocity * timeElapsed);
}

void Cliff::scaleCliff(float x, float y) {
    sf::Vector2f targetSize(x, y); 
    this->_sprite.setScale(
                            targetSize.x / this->_sprite.getLocalBounds().width, 
                            targetSize.y / this->_sprite.getLocalBounds().height
                            );
}

void Cliff::handleInput(sf::Event *event){}

void Cliff::generateCliffs(std::vector<Cliff*> &_cliffs, float velocity,int cliffsMax){

    int _cliffsMax = cliffsMax;
    for (int i=0; i< _cliffsMax ;i++){
        
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> ypos(100,200);
        std::uniform_real_distribution<float> size(100, 200);

        float direction = (rand() % 2 == 0);
        float altura = ypos(gen);
        
        std::vector<float> _cliffPos= {direction*DiveUp::SCREEN_WIDTH, altura};

        int sizex = size(gen)+100;
        int sizey = size(gen)+100;

        Cliff *cliff = new Cliff(sizex,sizey,direction,velocity);
        cliff->setPosition(_cliffPos.at(0), _cliffPos.at(1));

        if (i > 0){
            verifyCliffs(_cliffs, *cliff); 
            verifySpace(_cliffs, *cliff);}
    
        _cliffs.push_back(cliff);

    }
    //the lowest cliff must be over 500, so let's move all cliffs up
    for (Cliff *i : _cliffs){ i->setPosition(i->getPosition().x, i->getPosition().y-500); }
}


void Cliff::verifyCliffs(std::vector<Cliff*> &_cliffs, Cliff &cliff){

    sf::Rect<float> cliffBound = cliff.getBoundingRect();

    //verify if cliff is colliding with another cliff    
    for (int j=0; j< _cliffs.size(); j++){
        sf::Rect<float> targetBound = _cliffs.at(j)->getBoundingRect();
        if (cliffBound.intersects(targetBound)){
            std::vector<float> _cliffPos;
            float desplacement = ((rand() % 2 == 0) ? 1 : -1)*targetBound.height+100;
            _cliffPos = {cliff.getPosition().x, cliff.getPosition().y-desplacement};

            cliff.setPosition(_cliffPos.at(0), _cliffPos.at(1));
            verifyCliffs(_cliffs, cliff);
}}}

void Cliff::verifySpace(std::vector<Cliff*> &_cliffs, Cliff &cliff){
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
                
                cliff.scaleCliff(cliffBound.width-cliffBound.width*0.1, cliffBound.height);
                //sf::Rect<float> cliffBound = cliff.getBoundingRect();
                verifySpace(_cliffs, cliff);
                
}}}}
