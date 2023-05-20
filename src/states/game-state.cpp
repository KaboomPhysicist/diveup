#include "states/game-state.h"

GameState::~GameState() {}

void GameState::init(){};
void GameState::handleInput(sf::Event *event){};
void GameState::update(float timeElapsed){};
void GameState::draw(sf::RenderWindow *window){};

VisibleObjectManager *GameState::getObjectManager() {
  return &visibleObjectManager;
}