#include <iostream>
#include "app/Application.h"

void Application::initialize()
{
    std::cout << "Initializing Micromouse Simulator...\n";
    m_maze.initialize();

    // Thêm vài bức tường mẫu gần góc xuất phát (0,0)
    m_maze.setWall(0, 0, WALL_EAST);
    m_maze.setWall(0, 1, WALL_EAST);
    m_maze.setWall(1, 2, WALL_SOUTH);
}

void Application::run()
{
    std::cout << "16x16 Maze:\n\n";
    m_maze.printAscii();
}

void Application::shutdown()
{
    std::cout << "\nShutting down application.\n";
}