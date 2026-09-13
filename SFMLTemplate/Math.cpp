#include "Math.h"

namespace SnakeGame
{
    bool SamePosition(Position2D first, Position2D second)
    {
        return first.x == second.x && first.y == second.y;
    }
}