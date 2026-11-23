#include "ui/ConsoleRenderer.h"
#include <iostream>
#include <algorithm>

void ConsoleRenderer::render(const Maze& maze, const Robot& robot, const std::vector<Point>& path) const
{
    for (int y = Maze::SIZE - 1; y >= 0; --y)
    {
        for (int x = 0; x < Maze::SIZE; ++x)
        {
            std::cout << "+" << (maze.hasWall(x, y, WALL_NORTH) ? "---" : "   ");
        }
        std::cout << "+\n";

        for (int x = 0; x < Maze::SIZE; ++x)
        {
            std::cout << (maze.hasWall(x, y, WALL_WEST) ? "|" : " ");

            Point p{x, y};
            if (robot.getPosition() == p)
            {
                char dirChar = '^';
                if (robot.getDirection() == Direction::EAST)  dirChar = '>';
                if (robot.getDirection() == Direction::SOUTH) dirChar = 'v';
                if (robot.getDirection() == Direction::WEST)  dirChar = '<';
                std::cout << " " << dirChar << " ";
            }
            else if (maze.isGoal(p))
            {
                std::cout << " G ";
            }
            else if (maze.getStart() == p)
            {
                std::cout << " S ";
            }
            else if (std::find(path.begin(), path.end(), p) != path.end())
            {
                std::cout << " . ";
            }
            else
            {
                std::cout << "   ";
            }
        }
        std::cout << (maze.hasWall(Maze::SIZE - 1, y, WALL_EAST) ? "|" : " ") << "\n";
    }

    for (int x = 0; x < Maze::SIZE; ++x)
    {
        std::cout << "+" << (maze.hasWall(x, 0, WALL_SOUTH) ? "---" : "   ");
    }
    std::cout << "+\n";
}

void ConsoleRenderer::renderRobotStatus(const Robot& robot, const SensorReading& reading) const
{
    Point p = robot.getPosition();
    std::cout << "Vi tri robot: (" << p.x << ", " << p.y << ") | Cam bien tuong [Truoc: "
              << (reading.front ? "Co" : "Khong") << ", Trai: "
              << (reading.left ? "Co" : "Khong") << ", Phai: "
              << (reading.right ? "Co" : "Khong") << "]\n";
}

void ConsoleRenderer::renderStats(const SimulationStats& stats) const
{
    std::cout << "\n=== THONG KE KET QUA MO PHONG (" << stats.algorithmName << ") ===\n";
    std::cout << "- Trang thai   : " << (stats.goalReached ? "Den dich thanh cong!" : "Khong tim thay duong!") << "\n";
    std::cout << "- So buoc di   : " << stats.stepCount << " buoc\n";
    std::cout << "- Thoi gian CPU: " << stats.elapsedMs << " ms\n";
}