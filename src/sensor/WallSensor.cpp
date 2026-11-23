#include "sensor/WallSensor.h"

namespace
{
    Wall dirToWall(Direction dir)
    {
        switch (dir)
        {
            case Direction::NORTH: return WALL_NORTH;
            case Direction::EAST:  return WALL_EAST;
            case Direction::SOUTH: return WALL_SOUTH;
            case Direction::WEST:  return WALL_WEST;
        }
        return WALL_NONE;
    }
}

SensorReading WallSensor::read(const Maze& maze, const Robot& robot) const
{
    Point pos = robot.getPosition();
    Direction dir = robot.getDirection();

    Direction leftDir  = static_cast<Direction>((static_cast<int>(dir) + 3) % 4);
    Direction rightDir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);

    return {
        maze.hasWall(pos.x, pos.y, dirToWall(dir)),
        maze.hasWall(pos.x, pos.y, dirToWall(leftDir)),
        maze.hasWall(pos.x, pos.y, dirToWall(rightDir))
    };
}