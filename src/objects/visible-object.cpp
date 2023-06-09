#include "objects/visible-object.h"
#include <iostream>

VisibleObject::VisibleObject(std::string textureFilename) {
  if (!_texture.loadFromFile(textureFilename)) {
    std::cout << "Error while loading asset" << std::endl;
    return;
  }
  _isLoaded = true;
  _sprite.setTexture(_texture);
}

void VisibleObject::handleInput(sf::Event *event) {};
void VisibleObject::update(float timeElapsed) {};
void VisibleObject::collideWith(VisibleObject *target) {};

VisibleObject::~VisibleObject() {}

void VisibleObject::draw(sf::RenderWindow *window) {
  if (!_isLoaded) return;
  window->draw(_sprite);
}

void VisibleObject::move(float x, float y) {
  if (!_isLoaded) return;
  _sprite.move(x, y);
}

void VisibleObject::setPosition(float x, float y) {
    if (!_isLoaded) return;
    _sprite.setPosition(x, y);
}

sf::Vector2<float> VisibleObject::getPosition() {
    return _sprite.getPosition();
}

// Must be verified for non rectangular objects

float VisibleObject::getTop() {
  sf::Rect<float> boundingRect = getBoundingRect();
  return boundingRect.top;
}

float VisibleObject::getBottom() {
  sf::Rect<float> boundingRect = getBoundingRect();
  return boundingRect.top + boundingRect.height;
}

float VisibleObject::getLeft() {
  sf::Rect<float> boundingRect = getBoundingRect();
  return boundingRect.left;
}

float VisibleObject::getRight() {
  sf::Rect<float> boundingRect = getBoundingRect();
  return boundingRect.left + boundingRect.width;
}

sf::Rect<float> VisibleObject::getBoundingRect() {
    return _sprite.getGlobalBounds();
}

void VisibleObject::setPriority(size_t priority) {
    _priority = priority;
}

size_t VisibleObject::getPriority() {
    return _priority;
}

sf::Sprite VisibleObject::getSprite() {
    return _sprite;
}
