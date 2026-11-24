#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Cloneable.h"

// [NEW FILE] Optimising via Polymorphism

class Enemy
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

public:
    
    Enemy(float x, float y, float speed, int health) : speed(speed)
    {

    }

    virtual void update(float deltaTime)
    {
        speed = 0;
    }

    virtual void takeDamage()
    {
    }

};
