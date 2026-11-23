#ifndef MAZE_H
#define MAZE_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct Point
{
    int x = 0;
    int y = 0;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

enum Wall : uint8_t
{
    WALL_NONE  = 0,
    WALL_NORTH = 1 << 0, // 1
    WALL_EAST  = 1 << 1, // 2
    WALL_SOUTH = 1 << 2, // 4
    WALL_WEST  = 1 << 3  // 8
};

class Maze
{
public:
    static constexpr int SIZE = 16;

    Maze();
    void initialize();

    // Chỉnh sửa tường
    void setWall(int x, int y, Wall wall);
    void removeWall(int x, int y, Wall wall);
    bool hasWall(int x, int y, Wall wall) const;

    // Xuất phát & Đích
    void setStart(Point start);
    Point getStart() const;
    void setGoals(const std::vector<Point>& goals);
    const std::vector<Point>& getGoals() const;
    bool isGoal(Point p) const;

    // Lưu & Nạp mê cung
    bool saveToFile(const std::string& filePath) const;
    bool loadFromFile(const std::string& filePath);

private:
    std::array<std::array<uint8_t, SIZE>, SIZE> m_walls;
    Point m_start{0, 0};
    std::vector<Point> m_goals{{7, 7}, {7, 8}, {8, 7}, {8, 8}};
};

#endif