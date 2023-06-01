#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class VisibleObject {
    public:
      VisibleObject(std::string textureFilename);
      virtual ~VisibleObject();
      virtual void handleInput(sf::Event *event);
      virtual void update(float timeElapsed);
      virtual void draw(sf::RenderWindow *window);

      virtual void collideWith(VisibleObject *target);

      virtual void move(float x, float y);
      virtual void setPosition(float x, float y);
      virtual sf::Vector2<float> getPosition();

      virtual float getTop();
      virtual float getBottom();
      virtual float getLeft();
      virtual float getRight();

      // Useful for rectangular objects.
      virtual sf::Rect<float> getBoundingRect();

      virtual void setPriority(size_t priority);
      virtual size_t getPriority();

      virtual sf::Sprite getSprite();

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        bool _isLoaded;

    private:
      size_t _priority;
    };
