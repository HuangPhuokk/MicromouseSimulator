#include "robot/Robot.h"

Robot::Robot(Point startPos, Direction dir) : m_pos(startPos), m_dir(dir) {}

void Robot::reset(Point startPos, Direction dir)
{
    m_pos = startPos;
    m_dir = dir;
    m_state = RobotState::IDLE;
}

void Robot::moveForward()
{
    m_state = RobotState::MOVING;
    switch (m_dir)
    {
        case Direction::NORTH: m_pos.y += 1; break;
        case Direction::EAST:  m_pos.x += 1; break;
        case Direction::SOUTH: m_pos.y -= 1; break;
        case Direction::WEST:  m_pos.x -= 1; break;
    }
}

void Robot::turnLeft()
{
    m_dir = static_cast<Direction>((static_cast<int>(m_dir) + 3) % 4);
}

void Robot::turnRight()
{
    m_dir = static_cast<Direction>((static_cast<int>(m_dir) + 1) % 4);
}

void Robot::moveTo(Point nextPos)
{
    m_state = RobotState::MOVING;
    if (nextPos.x > m_pos.x)      m_dir = Direction::EAST;
    else if (nextPos.x < m_pos.x) m_dir = Direction::WEST;
    else if (nextPos.y > m_pos.y) m_dir = Direction::NORTH;
    else if (nextPos.y < m_pos.y) m_dir = Direction::SOUTH;
    m_pos = nextPos;
}

void Robot::setState(RobotState state) { m_state = state; }
RobotState Robot::getState() const { return m_state; }
Point Robot::getPosition() const { return m_pos; }
Direction Robot::getDirection() const { return m_dir; }