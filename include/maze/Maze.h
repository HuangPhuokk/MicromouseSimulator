#ifndef MAZE_H
#define MAZE_H

#include <array>
#include <cstdint>

enum Wall : uint8_t
{
    WALL_NONE  = 0,
    WALL_NORTH = 1 << 0, // Tường phía Bắc (1)
    WALL_EAST  = 1 << 1, // Tường phía Đông (2)
    WALL_SOUTH = 1 << 2, // Tường phía Nam (4)
    WALL_WEST  = 1 << 3  // Tường phía Tây (8)
};

class Maze
{
public:
    static constexpr int SIZE = 16;

    Maze();
    void initialize();
    void setWall(int x, int y, Wall wall);
    bool hasWall(int x, int y, Wall wall) const;
    void printAscii() const;

private:
    std::array<std::array<uint8_t, SIZE>, SIZE> m_walls;
};

#endif