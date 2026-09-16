#pragma once

#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    bool IsUp(sf::Keyboard::Key key);

    bool IsDown(sf::Keyboard::Key key);

    bool IsLeft(sf::Keyboard::Key key);

    bool IsRight(sf::Keyboard::Key key);

    bool IsBack(sf::Keyboard::Key key);

    bool IsConfirm(sf::Keyboard::Key key);

    bool IsPause(sf::Keyboard::Key key);
}