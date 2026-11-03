#include "Bullet.h"

Bullet::Bullet(float x, float y)
    : texture("assets/bullet.png"), sprite(texture) 
{
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(x, y));

    // Center horizontal origin of fired bullet
    sprite.setOrigin({ sprite.getGlobalBounds().size.x / 2.f, 0.f });

    speed = -400.f;
}

void Bullet::update(float deltaTime) {
    sprite.move(sf::Vector2f(0.f, speed * deltaTime));
}