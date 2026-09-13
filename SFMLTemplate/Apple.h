#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Math.h"

namespace SnakeGame
{
    struct Gamestate;

    struct Apples
    {
        int numApples = 1;

        std::vector<bool> isAppleEaten;
        std::vector<Position2D> applePos;
        std::vector<sf::Sprite> appleSprite;
    };

    bool FindFreeApplePosition(
        const Apples& apples,
        const Gamestate& game,
        Position2D& position
    );

    void InitApples(
        Apples& apples,
        const Gamestate& game
    );
}