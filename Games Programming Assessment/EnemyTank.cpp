#include "Enemy.h"

// [NEW FILE] Subclass of Enemy, Tank Enemy

class EnemyTank : public Enemy
{
	EnemyTank(float x, float y)
		: Enemy(x, y, 50, 30, sf::Texture("assets/tank_enemy_a.png"))
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