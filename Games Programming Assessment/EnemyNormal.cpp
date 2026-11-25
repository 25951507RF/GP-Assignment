#include "Enemy.h"

// [NEW FILE] Subclass of Enemy, Normal Enemy

class EnemyNormal : public Enemy
{
    EnemyNormal(float x, float y) 
        : Enemy(x, y, 60, 10, sf::Texture("assets/normal_enemy.png"))
    {
    }

    void update(float deltaTime) override
    {
        sprite.move(sf::Vector2f(0.f, speed * deltaTime));
    }

    void takeDamage() override
    {
        health -= 10;
    }
};