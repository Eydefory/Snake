#include "Input.h"

namespace SnakeGame
{
    bool IsUp(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::W ||
            key == sf::Keyboard::Up;
    }

    bool IsDown(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::S ||
            key == sf::Keyboard::Down;
    }

    bool IsLeft(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::A ||
            key == sf::Keyboard::Left;
    }

    bool IsRight(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::D ||
            key == sf::Keyboard::Right;
    }

    bool IsBack(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::B ||
            key == sf::Keyboard::Escape;
    }

    bool IsConfirm(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::Enter;
    }

    bool IsPause(sf::Keyboard::Key key)
    {
        return key == sf::Keyboard::P;
    }
}