#include "Apple.h"
#include "Game.h"

#include <cstdlib>

namespace SnakeGame
{
    bool IsApplePositionFree(
        const Apples& apples,
        const Gamestate& game,
        Position2D position)
    {
        for (const SnakeSegment& segment : game.snake.segments)
        {
            if (SamePosition(segment.position, position))
                return false;
        }

        for (int i = 0;
            i < static_cast<int>(apples.applePos.size());
            ++i)
        {
            if (!apples.isAppleEaten[i] &&
                SamePosition(apples.applePos[i], position))
            {
                return false;
            }
        }

        return true;
    }

    bool FindFreeApplePosition(
        const Apples& apples,
        const Gamestate& game,
        Position2D& position)
    {
        const int columns =
            SCREEN_WIDTH / static_cast<int>(APPLE_SIZE);

        const int rows =
            SCREEN_HEIGHT / static_cast<int>(APPLE_SIZE);

        for (int attempt = 0;
            attempt < columns * rows * 2;
            ++attempt)
        {
            position.x =
                static_cast<float>(
                    (1 + rand() % (columns - 2)) * APPLE_SIZE
                    );

            position.y =
                static_cast<float>(
                    (1 + rand() % (rows - 2)) * APPLE_SIZE
                    );

            if (IsApplePositionFree(
                apples,
                game,
                position))
            {
                return true;
            }
        }

        for (int y = 1;
            y < rows - 1;
            ++y)
        {
            for (int x = 1;
                x < columns - 1;
                ++x)
            {
                position.x =
                    static_cast<float>(x * APPLE_SIZE);

                position.y =
                    static_cast<float>(y * APPLE_SIZE);

                if (IsApplePositionFree(
                    apples,
                    game,
                    position))
                {
                    return true;
                }
            }
        }

        position.x = -1.f;
        position.y = -1.f;

        return false;
    }

    void InitApples(
        Apples& apples,
        const Gamestate& game)
    {
        apples.isAppleEaten.clear();
        apples.applePos.clear();
        apples.appleSprite.clear();

        for (int i = 0; i < apples.numApples; ++i)
        {
            Position2D position;

            if (!FindFreeApplePosition(
                apples,
                game,
                position))
            {
                break;
            }

            apples.applePos.push_back(position);
            apples.isAppleEaten.push_back(false);

            sf::Sprite sprite;

            sprite.setTexture(game.appleTexture);

            sprite.setScale(
                APPLE_SIZE /
                game.appleTexture.getSize().x,
                APPLE_SIZE /
                game.appleTexture.getSize().y
            );

            sprite.setPosition(
                position.x,
                position.y
            );

            apples.appleSprite.push_back(sprite);
        }
    }
}