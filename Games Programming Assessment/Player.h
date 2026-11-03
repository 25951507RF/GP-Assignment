#pragma once
#include <SFML/Graphics.hpp>

class Player 
{
public:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int health;
    int score;

    Player();

    // Updates player input and position each frame
    void update(float deltaTime);

    // Reduce player health by a given amount
    void takeDamage(int amount);
};