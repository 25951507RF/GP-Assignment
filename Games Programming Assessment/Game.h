#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Enemies.h"
#include "Bullet.h"

class GameManager 
{
private:
    sf::RenderWindow* window;
    Player* player;

    // Enemy containers storing raw pointers
    std::vector<NormalEnemy*> normalEnemies;
    std::vector<FastEnemy*> fastEnemies;
    std::vector<TankEnemy*> tankEnemies;
    std::vector<Bullet*> bullets;

    // Textures for game objects
    sf::Texture playerTex;
    sf::Texture normalEnemyTex;
    sf::Texture fastEnemyTex;
    sf::Texture tankEnemyTex;
    sf::Texture bulletTex;

    // Audio buffers and sound player instances
    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    sf::SoundBuffer explosionLongBuffer;
    sf::Sound explosionLongSound;
    sf::SoundBuffer explosionLowBuffer;
    sf::Sound explosionLowSound;

    // Font and UI Text overlays
    sf::Font font;
    sf::Text uiText;
    sf::Text overlayText;

    // Tower defense line elements
    sf::RectangleShape towerLine;
    float maxLineWidth;
    float currentLineWidth;

    // Spawning and state management flags
    float enemySpawnTimer;
    int gameState; // 0 = Menu, 1 = Playing, 2 = Paused, 3 = GameOver
    int windowWidth;
    int windowHeight;
    bool canFire;
    bool pauseKeyPressed;

public:
    GameManager(int windowWidth, int windowHeight);
    ~GameManager();

    void update(float deltaTime); //run every frame to update game
    void draw();                  //render updated game state
    void resetGame();             //reset entire game to its initial state configurations

    // Return pointer to game window
    sf::RenderWindow* getWindow();

    // Spawner helpers
    void spawnNormalEnemy();
    void spawnFastEnemy();
    void spawnTankEnemy();

    // Firing helpers
    void firePlayerBullet();
};