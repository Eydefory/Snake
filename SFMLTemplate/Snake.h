#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
    enum class snakeDir
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct SnakeSegment
    {
        Position2D position;
        snakeDir direction = snakeDir::Right;
        sf::Sprite sprite;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        snakeDir direction = snakeDir::Right;
        float snakeSpeed = DIFFICULTY_SPEEDS[0];
        bool isAlive = true;
    };

    
}