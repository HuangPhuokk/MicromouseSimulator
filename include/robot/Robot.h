#ifndef ROBOT_H
#define ROBOT_H

#include "maze/Maze.h"

enum class Direction
{
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3
};

enum class RobotState
{
    IDLE,
    MOVING,
    REACHED_GOAL,
    STUCK
};

class Robot
{
public:
    Robot(Point startPos = {0, 0}, Direction dir = Direction::NORTH);

    void reset(Point startPos = {0, 0}, Direction dir = Direction::NORTH);
    void moveForward();
    void turnLeft();
    void turnRight();
    void moveTo(Point nextPos);

    void setState(RobotState state);
    RobotState getState() const;
    Point getPosition() const;
    Direction getDirection() const;

private:
    Point m_pos;
    Direction m_dir;
    RobotState m_state = RobotState::IDLE;
};

#endif