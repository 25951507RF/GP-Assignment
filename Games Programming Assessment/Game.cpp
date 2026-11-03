#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

GameManager::GameManager(int windowWidth, int windowHeight):
    windowWidth(windowWidth), windowHeight(windowHeight), maxLineWidth(windowWidth),
    fireBuffer("assets/fire.ogg"), fireSound(fireBuffer),
    explosionBuffer("assets/explosion.ogg"), explosionSound(explosionBuffer),
    explosionLongBuffer("assets/explosion_long.ogg"), explosionLongSound(explosionLongBuffer),
    explosionLowBuffer("assets/explosion_low.ogg"), explosionLowSound(explosionLowBuffer),
    playerTex("assets/player.png"), normalEnemyTex("assets/normal_enemy.png"),
    fastEnemyTex("assets/fast_enemy.png"), tankEnemyTex("assets/tank_enemy_a.png"),
    bulletTex("assets/bullet.png"), font("assets/arial.ttf"),
    uiText(font), overlayText(font) 
{
    window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Space Shooter");
    player = new Player();
    enemySpawnTimer = 0.f;
    gameState = 1;
    canFire = true;
    pauseKeyPressed = false;

    // Initialize Tower Defense Line
    currentLineWidth = maxLineWidth;
    towerLine.setSize({ currentLineWidth, 6.f });
    towerLine.setFillColor(sf::Color(72, 199, 255));
    towerLine.setPosition(sf::Vector2f(0.f, (windowHeight - 10)));

    // Configure HUD and Overlay Text
    uiText.setFont(font);
    uiText.setCharacterSize(30);
    uiText.setFillColor(sf::Color::White);

    overlayText.setFont(font);
    overlayText.setCharacterSize(30);
    overlayText.setFillColor(sf::Color(255, 204, 0));
}

GameManager::~GameManager() 
{
    delete window;
}

void GameManager::resetGame() 
{
    // Clear vectors storing game objects
    normalEnemies.clear();
    fastEnemies.clear();
    tankEnemies.clear();
    bullets.clear();

    // Reset player stats & position
    player->health = 100;
    player->score = 0;
    player->sprite.setPosition(sf::Vector2f(windowWidth / 2, windowHeight - 80));

    // Reset Tower Defense Line
    currentLineWidth = maxLineWidth;
    towerLine.setSize({ currentLineWidth, 6.f });
    towerLine.setPosition(sf::Vector2f(0.f, windowHeight - 10));

    //Reset spawn timer and set game state to playing
    enemySpawnTimer = 0.f;
    gameState = 1;
}

//Spawn normal enemy and add to normal enemy vector container
void GameManager::spawnNormalEnemy() 
{
    float x = (rand() % 700 + 20);
    normalEnemies.push_back(new NormalEnemy(x, -10.f));
}

//Spawn fast enemy and add to fast enemy vector container
void GameManager::spawnFastEnemy() 
{
    float x = (rand() % 700 + 20);
    fastEnemies.push_back(new FastEnemy(x, -10.f));
}

//Spawn tank enemy and add to tank enemy vector container
void GameManager::spawnTankEnemy() 
{
    float x = (rand() % 600 + 50);
    tankEnemies.push_back(new TankEnemy(x, -20.f));
}

//Fire bullet and play laser sound
void GameManager::firePlayerBullet() 
{
    bullets.push_back(new Bullet(player->sprite.getPosition().x + player->sprite.getGlobalBounds().size.x / 2, player->sprite.getPosition().y));
    fireSound.play();
}

//Update game
void GameManager::update(float deltaTime) 
{
    // Pause state toggle ('P' key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) 
    {
        if (!pauseKeyPressed) 
        {
            if (gameState == 1) gameState = 2;      // Pause
            else if (gameState == 2) gameState = 1; // Unpause
            pauseKeyPressed = true;
        }
    }
    else 
    {
        pauseKeyPressed = false;
    }

    // Restart game when in Game Over screen ('R' key)
    if (gameState == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) 
    {
        resetGame();
    }

    // Active Gameplay Update Loop
    if (gameState == 1) 
    {
        player->update(deltaTime);

        // Handle random enemy spawning
        enemySpawnTimer += deltaTime;
        if (enemySpawnTimer > 2.f) 
        {
            int r = rand() % 3;
            if (r == 0) spawnNormalEnemy();
            else if (r == 1) spawnFastEnemy();
            else spawnTankEnemy();

            enemySpawnTimer = 0.f;
        }

        // Handle bullet firing
        if (canFire && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
        {
            canFire = false;
            firePlayerBullet();
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
        {
            canFire = true;
        }

        // Update movement on all enemies stored in all enemy containers
        for (int i = 0; i < normalEnemies.size(); ++i) normalEnemies[i]->update(deltaTime);
        for (int i = 0; i < fastEnemies.size(); ++i) fastEnemies[i]->update(deltaTime);
        for (int i = 0; i < tankEnemies.size(); ++i) tankEnemies[i]->update(deltaTime);
        for (int i = 0; i < bullets.size(); ++i) bullets[i]->update(deltaTime);

        // Check for collisions between bullets & normal enemies
        int i1 = 0;
        while (i1 < bullets.size())
        {
            bool bulletErased = false;
            int j = 0;
            while (j < normalEnemies.size())
            {
                if (bullets[i1]->sprite.getGlobalBounds().findIntersection(normalEnemies[j]->sprite.getGlobalBounds()))
                {
                    explosionSound.play();
                    normalEnemies[j]->takeDamage();
                    bullets.erase(bullets.begin() + i1);
                    bulletErased = true;

                    if (normalEnemies[j]->health <= 0)
                    {
                        normalEnemies.erase(normalEnemies.begin() + j);
                        player->score += 10;
                    }
                    break;
                }
                ++j;
            }
            if (!bulletErased) ++i1;
        }

        // Check for collisions between bullets & fast enemies
        int i2 = 0;
        while (i2 < bullets.size())
        {
            bool bulletErased = false;
            int j = 0;
            while (j < fastEnemies.size())
            {
                if (bullets[i2]->sprite.getGlobalBounds().findIntersection(fastEnemies[j]->sprite.getGlobalBounds()))
                {
                    explosionSound.play();
                    fastEnemies[j]->takeDamage();
                    bullets.erase(bullets.begin() + i2);
                    bulletErased = true;

                    if (fastEnemies[j]->health <= 0)
                    {
                        fastEnemies.erase(fastEnemies.begin() + j);
                        player->score += 10;
                    }
                    break;
                }
                ++j;
            }
            if (!bulletErased) ++i2;
        }

        // Check for collisions between bullets & tank enemies
        int i3 = 0;
        while (i3 < bullets.size())
        {
            bool bulletErased = false;
            int j = 0;
            while (j < tankEnemies.size())
            {
                if (bullets[i3]->sprite.getGlobalBounds().findIntersection(tankEnemies[j]->sprite.getGlobalBounds()))
                {
                    explosionSound.play();
                    tankEnemies[j]->takeDamage();

                    bullets.erase(bullets.begin() + i3);
                    bulletErased = true;

                    // Update dynamic damage textures or remove enemy if its health is depleted
                    if (tankEnemies[j]->health <= 0)
                    {
                        tankEnemies.erase(tankEnemies.begin() + j);
                    }
                    else if (tankEnemies[j]->health <= 10)
                    {
                        tankEnemies[j]->texture.loadFromFile("assets/tank_enemy_c.png");
                    }
                    else if (tankEnemies[j]->health <= 20)
                    {
                        tankEnemies[j]->texture.loadFromFile("assets/tank_enemy_b.png");
                    }

                    player->score += 10;
                    break;
                }
                ++j;
            }
            if (!bulletErased) ++i3;
        }

        // Check for collisions between player & normal enemies
        int i4 = 0;
        while (i4 < normalEnemies.size())
        {
            if (player->sprite.getGlobalBounds().findIntersection(normalEnemies[i4]->sprite.getGlobalBounds()))
            {
                player->health -= 20;
                if (player->health <= 0)
                {
                    explosionLongSound.play();
                }
                else
                {
                    explosionSound.play();
                }
                normalEnemies.erase(normalEnemies.begin() + i4);
            }
            else
            {
                ++i4;
            }
        }

        // Check for collisions between player & fast enemies
        int i5 = 0;
        while (i5 < fastEnemies.size())
        {
            if (player->sprite.getGlobalBounds().findIntersection(fastEnemies[i5]->sprite.getGlobalBounds()))
            {
                player->health -= 15;
                if (player->health <= 0)
                {
                    explosionLongSound.play();
                }
                else
                {
                    explosionSound.play();
                }
                fastEnemies.erase(fastEnemies.begin() + i5);
            }
            else
            {
                ++i5;
            }
        }

        // Check for collisions between player & tank enemies
        int i6 = 0;
        while (i6 < tankEnemies.size())
        {
            if (player->sprite.getGlobalBounds().findIntersection(tankEnemies[i6]->sprite.getGlobalBounds()))
            {
                player->health -= 40;
                if (player->health <= 0)
                {
                    explosionLongSound.play();
                }
                else
                {
                    explosionSound.play();
                }
                tankEnemies.erase(tankEnemies.begin() + i6);
            }
            else
            {
                ++i6;
            }
        }

        // Check for collisions between enemies & tower defense line
        float floorLevel = (windowHeight - 10);

        int i7 = 0;
        while (i7 < normalEnemies.size())
        {
            if (normalEnemies[i7]->sprite.getPosition().y + normalEnemies[i7]->sprite.getGlobalBounds().size.y >= floorLevel)
            {
                currentLineWidth -= 40.f;
                explosionLowSound.play();
                normalEnemies.erase(normalEnemies.begin() + i7);
            }
            else
            {
                ++i7;
            }
        }

        int i8 = 0;
        while (i8 < fastEnemies.size())
        {
            if (fastEnemies[i8]->sprite.getPosition().y + fastEnemies[i8]->sprite.getGlobalBounds().size.y >= floorLevel)
            {
                currentLineWidth -= 25.f;
                explosionLowSound.play();
                fastEnemies.erase(fastEnemies.begin() + i8);
            }
            else
            {
                ++i8;
            }
        }

        int i9 = 0;
        while (i9 < tankEnemies.size())
        {
            if (tankEnemies[i9]->sprite.getPosition().y + tankEnemies[i9]->sprite.getGlobalBounds().size.y >= floorLevel)
            {
                currentLineWidth -= 100.f;
                explosionLowSound.play();
                tankEnemies.erase(tankEnemies.begin() + i9);
            }
            else
            {
                ++i9;
            }
        }

        // Clamp tower defense line width minimum and keep centered
        if (currentLineWidth < 0.f) 
        {
            currentLineWidth = 0.f;
        }

        float centeredX = (windowWidth - currentLineWidth) / 2.f;
        towerLine.setSize({ currentLineWidth, 6.f });
        towerLine.setPosition(sf::Vector2f(centeredX, windowHeight - 10));

        // Check and trigger game over
        if (player->health <= 0 || currentLineWidth <= 0.f) 
        {
            if (player->health < 0) player->health = 0;
            gameState = 3;
        }
    }

    //call to render update game state
    draw();
}

//return a pointer to the game window object
sf::RenderWindow* GameManager::getWindow() 
{
    return window;
}

//Draw all game objects and text
void GameManager::draw() 
{
    window->clear(sf::Color(20, 20, 30));

    // Render player & dynamic game entities
    window->draw(player->sprite);
    for (auto e : normalEnemies) window->draw(e->sprite);
    for (auto e : fastEnemies) window->draw(e->sprite);
    for (auto e : tankEnemies) window->draw(e->sprite);
    for (auto b : bullets) window->draw(b->sprite);

    // Draw Defense Line if active
    if (currentLineWidth > 0.f) 
    {
        window->draw(towerLine);
    }

    // Draw HUD text
    uiText.setString("Health: " + std::to_string(player->health) + " | Score: " + std::to_string(player->score));
    window->draw(uiText);

    // Draw Pause / Game Over overlays
    if (gameState == 2) 
    {
        overlayText.setString("     GAME PAUSED\nPress 'P' to Resume");
        overlayText.setPosition(sf::Vector2f(windowWidth / 2 - 100, windowHeight / 2 - 40));
        window->draw(overlayText);
    }
    else if (gameState == 3) 
    {
        overlayText.setString("        GAME OVER\nPress 'R' to Restart");
        overlayText.setPosition(sf::Vector2f(windowWidth / 2 - 100, windowHeight / 2 - 40));
        window->draw(overlayText);
    }

    window->display();
}