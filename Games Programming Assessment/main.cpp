#include "Game.h"

int main()
{
    // Declare window dimensions as constants to avoid magic numbers
    constexpr int WIN_WIDTH = 800;
    constexpr int WIN_HEIGHT = 600;

    // Instantiate the game manager
    GameManager game(WIN_WIDTH, WIN_HEIGHT);
    sf::RenderWindow* window = game.getWindow();

    // Clock used for frame time delta computation
    sf::Clock clock;

    // Main game loop
    while (window->isOpen())
    {
        // Calculate frame delta time in seconds
        float deltaTime = clock.restart().asSeconds();

        // Process OS and window events
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window->close();
        }

        // Frame rendering cycle
        window->clear();
        game.update(deltaTime);
        game.draw();
        window->display();
    }

    return 0;
}