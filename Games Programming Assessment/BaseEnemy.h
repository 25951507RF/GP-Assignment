#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

   virtual void update(float deltaTime);
    void takeDamage();

};
