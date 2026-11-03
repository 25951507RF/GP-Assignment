#pragma once
#include <SFML/Graphics.hpp>

// Standard enemy type with standard health and speed
class NormalEnemy 
{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

    // Reserved array used to analyze memory allocations and test memory leaks
    int memoryTestingArray[400000];

    NormalEnemy(float x, float y);
    void update(float deltaTime);
    void takeDamage();
};

// Fast-moving enemy type with standard health
class FastEnemy 
{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

    // Reserved array used to analyze memory allocations and test memory leaks
    int memoryTestingArray[400000];

    FastEnemy(float x, float y);
    void update(float deltaTime);
    void takeDamage();
};

// High-health enemy type
class TankEnemy 
{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    int health;

    // Reserved array used to analyze memory allocations and test memory leaks
    int memoryTestingArray[4000];

    TankEnemy(float x, float y);
    void update(float deltaTime);
    void takeDamage();
};