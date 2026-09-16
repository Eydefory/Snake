#include "Game.h"

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>

int main()
{
    using namespace SnakeGame;

    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)
            )
    );

    sf::RenderWindow window(
        sf::VideoMode(
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        ),
        "Snake Game"
    );

    window.setFramerateLimit(60);

    Gamestate game;

    InitGame(game);

    sf::Clock gameClock;

    while (window.isOpen())
    {
        const float deltaTime =
            gameClock.restart().asSeconds();

        HandleEvents(game, window);

        UpdateGame(
            game,
            deltaTime,
            window
        );

        DrawGame(
            game,
            window
        );
    }

    return 0;
}