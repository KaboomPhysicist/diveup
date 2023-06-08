#include "objects/entities/cliff.h"
#include "diveup.h"

Cliff::Cliff(int sizex, int sizey, float dir, float speed) : VisibleObject("assets/cliff1.png") { 
    sf::Vector2f targetSize(sizex, sizey);
    this->direction = dir;
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

Triangle* Cliff::getTriangle(){

    float xcoord = (direction == 1.0f) ? getRight() : getLeft();
    float x2coord = (direction == 1.0f) ? (getLeft() + 20) : (getRight() - 20);

    sf::Vector2f topVertex = {xcoord, getTop()};
    sf::Vector2f bottomVertex = {xcoord, getBottom() - 20};
    sf::Vector2f middleVertex = {x2coord, getTop()};

    triangle = new Triangle(topVertex, bottomVertex, middleVertex);

    return triangle;
}

void Cliff::collideWith(VisibleObject *target) {
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

        std::normal_distribution<float> ypos(0, 50);
        std::normal_distribution<float> size(100, 50);

        float direction = (rand() % 2 == 0);
        float altura = ypos(gen);
        
        std::vector<float> _cliffPos= {direction*DiveUp::SCREEN_WIDTH, altura};

        int sizex = size(gen)+100;
        int sizey = size(gen)+100;


        //std::cout << "size: " << sizex << " " << sizey << std::endl;

        Cliff *cliff = new Cliff(sizex, sizey, direction, velocity);

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
