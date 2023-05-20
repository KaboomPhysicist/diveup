#include "states/game-state.h"

GameState::~GameState() {}

VisibleObjectManager *GameState::getObjectManager() {
  return &visibleObjectManager;
}