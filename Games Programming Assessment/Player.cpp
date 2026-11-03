#include "Player.h"

Player::Player()
    : texture("assets/player.png"), sprite(texture) 
{
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(400.f, 500.f));
    speed = 300.f;
    health = 100;
    score = 0;
}

void Player::update(float deltaTime) 
{
    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
    {
        sprite.move(sf::Vector2f(-speed * deltaTime, 0.f));
    }

    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
    {
        sprite.move(sf::Vector2f(speed * deltaTime, 0.f));
    }
}

void Player::takeDamage(int amount) 
{
    health -= amount;
}