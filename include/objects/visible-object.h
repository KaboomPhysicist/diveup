#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class VisibleObject {
    public:
    VisibleObject(std::string textureFilename);
    virtual ~VisibleObject();
    virtual void handleInput(sf::Event *event) {};
    virtual void update(float timeElapsed) = 0;
    virtual void draw(sf::RenderWindow *window);

    virtual void collideWith(VisibleObject *target) {};

    virtual void move(float x, float y);
    virtual void setPosition(float x, float y);
    virtual sf::Vector2<float> getPosition();

    virtual float getTop();
    virtual float getBottom();
    virtual float getLeft();
    virtual float getRight();

    // Useful for rectangular objects.
    virtual sf::Rect<float> getBoundingRect();

    private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    bool _isLoaded;
    };
