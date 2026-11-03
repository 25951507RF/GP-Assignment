#pragma once
#include <SFML/Graphics.hpp>

class Bullet 
{
public:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;

    Bullet(float x, float y);

    // Updates bullet movement upwards each frame
    void update(float deltaTime);

    // Reserved array used to analyze memory allocations and test memory leaks
    int memoryTestingArray[400000];
};