#include "Enemies.h"

// Normal Enemy Implementation
NormalEnemy::NormalEnemy(float x, float y) 
    : texture("assets/normal_enemy.png"), sprite(texture) 
{    
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(x, y));
    speed = 60.f;
    health = 10;
}

void NormalEnemy::update(float deltaTime) 
{
    sprite.move(sf::Vector2f(0.f, speed * deltaTime));
}

void NormalEnemy::takeDamage() 
{
    health -= 10;
}

// Fast Enemy Implementation
FastEnemy::FastEnemy(float x, float y) 
    : texture("assets/fast_enemy.png"), sprite(texture) 
{
    
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(x, y));
    speed = 120.f;
    health = 10;
}

void FastEnemy::update(float deltaTime) 
{
    sprite.move(sf::Vector2f(0.f, speed * deltaTime));
}

void FastEnemy::takeDamage() 
{
    health -= 10;
}

// Tank Enemy Implementation
TankEnemy::TankEnemy(float x, float y) 
    : texture("assets/tank_enemy_a.png"), sprite(texture) 
{    
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(x, y));
    speed = 50.f;
    health = 30;
}

void TankEnemy::update(float deltaTime) 
{
    sprite.move(sf::Vector2f(0.f, speed * deltaTime));
}

void TankEnemy::takeDamage() 
{
    health -= 10;
}