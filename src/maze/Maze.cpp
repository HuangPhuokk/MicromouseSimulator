#include "maze/Maze.h"
#include <fstream>
#include <algorithm>

Maze::Maze()
{
    initialize();
}

void Maze::initialize()
{
    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            m_walls[y][x] = WALL_NONE;
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        setWall(i, 0, WALL_SOUTH);
        setWall(i, SIZE - 1, WALL_NORTH);
        setWall(0, i, WALL_WEST);
        setWall(SIZE - 1, i, WALL_EAST);
    }

    m_start = {0, 0};
    m_goals = {{7, 7}, {7, 8}, {8, 7}, {8, 8}};
}

void Maze::setWall(int x, int y, Wall wall)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return;
    m_walls[y][x] |= wall;

    if (wall == WALL_NORTH && y + 1 < SIZE)      m_walls[y + 1][x] |= WALL_SOUTH;
    else if (wall == WALL_SOUTH && y - 1 >= 0)   m_walls[y - 1][x] |= WALL_NORTH;
    else if (wall == WALL_EAST && x + 1 < SIZE)  m_walls[y][x + 1] |= WALL_WEST;
    else if (wall == WALL_WEST && x - 1 >= 0)    m_walls[y][x - 1] |= WALL_EAST;
}

void Maze::removeWall(int x, int y, Wall wall)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return;
    m_walls[y][x] &= ~wall;

    if (wall == WALL_NORTH && y + 1 < SIZE)      m_walls[y + 1][x] &= ~WALL_SOUTH;
    else if (wall == WALL_SOUTH && y - 1 >= 0)   m_walls[y - 1][x] &= ~WALL_NORTH;
    else if (wall == WALL_EAST && x + 1 < SIZE)  m_walls[y][x + 1] &= ~WALL_WEST;
    else if (wall == WALL_WEST && x - 1 >= 0)    m_walls[y][x - 1] &= ~WALL_EAST;
}

bool Maze::hasWall(int x, int y, Wall wall) const
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return true;
    return (m_walls[y][x] & wall) != 0;
}

void Maze::setStart(Point start) { m_start = start; }
Point Maze::getStart() const { return m_start; }
void Maze::setGoals(const std::vector<Point>& goals) { m_goals = goals; }
const std::vector<Point>& Maze::getGoals() const { return m_goals; }

bool Maze::isGoal(Point p) const
{
    return std::find(m_goals.begin(), m_goals.end(), p) != m_goals.end();
}

bool Maze::saveToFile(const std::string& filePath) const
{
    std::ofstream out(filePath);
    if (!out.is_open()) return false;

    for (int y = SIZE - 1; y >= 0; --y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            out << static_cast<int>(m_walls[y][x]) << (x == SIZE - 1 ? "" : " ");
        }
        out << "\n";
    }
    return true;
}

bool Maze::loadFromFile(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in.is_open()) return false;

    for (int y = SIZE - 1; y >= 0; --y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            int val = 0;
            if (!(in >> val)) return false;
            m_walls[y][x] = static_cast<uint8_t>(val);
        }
    }
    return true;
}