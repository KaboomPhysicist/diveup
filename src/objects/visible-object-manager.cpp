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
  }
}