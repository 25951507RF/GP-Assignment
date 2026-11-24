#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Cloneable.h"

// [NEW FILE] Optimising via Polymorphism

class Enemy : public ICloneable
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

public:

    Enemy(float x, float y) :
        texture("assets/normal_enemy.png"), sprite(texture)
    {
        sprite.setTexture(texture, true);
        sprite.setPosition(sf::Vector2f(x, y));
        speed = 60.f;
        health = 10;
    }

    virtual void update(float deltaTime)
    {
        sprite.move(sf::Vector2f(0.f, speed * deltaTime));
    }

    void takeDamage()
    {
        health -= 10;
    }

};
