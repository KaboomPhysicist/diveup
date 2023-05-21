#include "objects/visible-object-manager.h"

// Delete the objects from the map
VisibleObjectManager::~VisibleObjectManager() {
    auto itr = _objects.begin();
        while (itr != _objects.end()) {
            delete itr->second;
            itr++;
  }
}

// Add objects to the map
void VisibleObjectManager::add(std::string name, VisibleObject *object) {
    _objects.insert(std::pair<std::string, VisibleObject*>(name, object));
}

// Delete a specific object from the map
void VisibleObjectManager::remove(std::string name) {
    auto results = _objects.find(name);
    if (results != _objects.end()) {
        delete results->second;
        _objects.erase(results);
        //std::cout << "Object " << name << " removed" << std::endl;
  }
}

VisibleObject *VisibleObjectManager::get(std::string name) {
  auto results = _objects.find(name);
  if (results == _objects.end()) return NULL;
  return results->second;
}

void VisibleObjectManager::handleInputAll(sf::Event *event) {
  auto itr = _objects.begin();
  while (itr != _objects.end()) {
    itr->second->handleInput(event);
    itr++;
  }
}

void VisibleObjectManager::updateAll(float timeElapsed) {
  auto itr = _objects.begin();
  while (itr != _objects.end()) {
    itr->second->update(timeElapsed);
    itr++;
  }  // Detect collision. 
  // This could be improved in a lot of way but give us a starting point
  auto originItr = _objects.begin();  while (originItr != _objects.end()) {
    sf::Rect<float> originBound = originItr->second->getBoundingRect();
    auto targetItr = _objects.begin();    while (targetItr != _objects.end()) {
      if (targetItr == originItr) { targetItr++; continue; }
      
      sf::Rect<float> targetBound = targetItr->second->getBoundingRect();      if (originBound.intersects(targetBound)) {
        originItr->second->collideWith(targetItr->second);
      }
      targetItr++;
    }
    originItr++;
  }
}

void VisibleObjectManager::drawAll(sf::RenderWindow *window) {

  // Create a multimap to order the objects by priority
  std::multimap<size_t, VisibleObject*> *_orderedObjects = new std::multimap<size_t, VisibleObject*>();

  // Fills the multimap
  auto itr = _objects.begin();
  while (itr != _objects.end()) {
    //std::cout << "Object " << itr->first << " added to the ordered list" << std::endl;
    _orderedObjects->insert(std::make_pair(itr->second->getPriority(), itr->second));
    itr++;
  }

  // Draw the objects in order of priority
  for(auto& pair : *_orderedObjects) {
    pair.second->draw(window);
  }


  delete  _orderedObjects;
}