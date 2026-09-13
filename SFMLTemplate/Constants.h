#pragma once

namespace SnakeGame
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    const float PLAYER_SIZE = 20.f;
    const float APPLE_SIZE = 20.f;

    
    const float START_DELAY = 2.f;

    const int INITIAL_SNAKE_LENGTH = 3;
    const int GROWTH_PER_APPLE = 1;

    const int MIN_DIFFICULTY = 1;
    const int MAX_DIFFICULTY = 5;

   
    const float DIFFICULTY_SPEEDS[MAX_DIFFICULTY] =
    {
        70.f, 90.f, 110.f, 130.f, 150.f
    };

    const int DIFFICULTY_POINTS[MAX_DIFFICULTY] =
    {
        2, 4, 6, 8, 10
    };
}
