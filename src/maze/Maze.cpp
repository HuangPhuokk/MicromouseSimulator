#include "maze/Maze.h"
#include <iostream>

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

    // Dựng tường bao quanh 4 biên ngoài của mê cung 16x16
    for (int i = 0; i < SIZE; ++i)
    {
        setWall(i, 0, WALL_SOUTH);        // Biên dưới (y = 0)
        setWall(i, SIZE - 1, WALL_NORTH); // Biên trên (y = 15)
        setWall(0, i, WALL_WEST);         // Biên trái (x = 0)
        setWall(SIZE - 1, i, WALL_EAST);  // Biên phải (x = 15)
    }
}

void Maze::setWall(int x, int y, Wall wall)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return;

    m_walls[y][x] |= wall;

    // Tự động dựng bức tường tương ứng ở ô liền kề
    if (wall == WALL_NORTH && y + 1 < SIZE)      m_walls[y + 1][x] |= WALL_SOUTH;
    else if (wall == WALL_SOUTH && y - 1 >= 0)   m_walls[y - 1][x] |= WALL_NORTH;
    else if (wall == WALL_EAST && x + 1 < SIZE)  m_walls[y][x + 1] |= WALL_WEST;
    else if (wall == WALL_WEST && x - 1 >= 0)    m_walls[y][x - 1] |= WALL_EAST;
}

bool Maze::hasWall(int x, int y, Wall wall) const
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return true;
    return (m_walls[y][x] & wall) != 0;
}

void Maze::printAscii() const
{
    for (int y = SIZE - 1; y >= 0; --y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            std::cout << "+" << (hasWall(x, y, WALL_NORTH) ? "---" : "   ");
        }
        std::cout << "+\n";

        for (int x = 0; x < SIZE; ++x)
        {
            std::cout << (hasWall(x, y, WALL_WEST) ? "|" : " ") << "   ";
        }
        std::cout << (hasWall(SIZE - 1, y, WALL_EAST) ? "|" : " ") << "\n";
    }

    for (int x = 0; x < SIZE; ++x)
    {
        std::cout << "+" << (hasWall(x, 0, WALL_SOUTH) ? "---" : "   ");
    }
    std::cout << "+\n";
}