#include "Enemy.h"

// [NEW FILE] Subclass of Enemy, Fast Enemy

class EnemyFast : public Enemy
{
	EnemyFast(float x, float y)
		: Enemy(x, y, 120, 10, sf::Texture("assets/fast_enemy.png"))
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