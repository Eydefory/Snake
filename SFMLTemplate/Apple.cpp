#include "Apple.h"
#include "Game.h"

#include <cstdlib>

namespace SnakeGame
{
    static Position2D RandomFreePosition(const Apples& apples, const Gamestate& game)
    {
        const int columns = SCREEN_WIDTH / static_cast<int>(APPLE_SIZE);
        const int rows = SCREEN_HEIGHT / static_cast<int>(APPLE_SIZE);

        Position2D position;

       
        for (int attempt = 0; attempt < columns * rows * 2; ++attempt)
        {
            position.x = static_cast<float>((1 + rand() % (columns - 2)) * APPLE_SIZE);
            position.y = static_cast<float>((1 + rand() % (rows - 2)) * APPLE_SIZE);

            bool occupied = false;

            for (const SnakeSegment& segment : game.snake.segments)
            {
                if (segment.position.x == position.x &&
                    segment.position.y == position.y)
                {
                    occupied = true;
                    break;
                }
            }

            if (!occupied)
            {
                for (int i = 0; i < static_cast<int>(apples.applePos.size()); ++i)
                {
                    if (!apples.isAppleEaten[i] &&
                        apples.applePos[i].x == position.x &&
                        apples.applePos[i].y == position.y)
                    {
                        occupied = true;
                        break;
                    }
                }
            }

            if (!occupied)
                return position;
        }

        for (int y = 1; y < rows - 1; ++y)
        {
            for (int x = 1; x < columns - 1; ++x)
            {
                position.x = static_cast<float>(x * APPLE_SIZE);
                position.y = static_cast<float>(y * APPLE_SIZE);

                bool occupied = false;
                for (const SnakeSegment& segment : game.snake.segments)
                {
                    if (segment.position.x == position.x &&
                        segment.position.y == position.y)
                    {
                        occupied = true;
                        break;
                    }
                }

                if (!occupied)
                    return position;
            }
        }

        return Position2D{-1.f, -1.f};
    }

    void InitApples(Apples& apples, const Gamestate& game)
    {
        apples.isAppleEaten.clear();
        apples.applePos.clear();
        apples.appleSprite.clear();

        for (int i = 0; i < apples.numApples; ++i)
        {
            Position2D position = RandomFreePosition(apples, game);
            if (position.x < 0.f)
                break;

            apples.applePos.push_back(position);
            apples.isAppleEaten.push_back(false);

            sf::Sprite sprite;
            sprite.setTexture(game.appleTexture);
            sprite.setScale(
                APPLE_SIZE / game.appleTexture.getSize().x,
                APPLE_SIZE / game.appleTexture.getSize().y
            );
            sprite.setPosition(position.x, position.y);

            apples.appleSprite.push_back(sprite);
        }
    }
}
