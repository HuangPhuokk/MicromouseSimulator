#include "simulation/Simulator.h"
#include <chrono>
#include <iostream>

void Simulator::setupSampleMaze()
{
    m_maze.initialize();

    // Tạo hệ thống vách ngăn mẫu
    m_maze.setWall(0, 0, WALL_EAST);
    m_maze.setWall(0, 1, WALL_EAST);
    m_maze.setWall(0, 2, WALL_EAST);
    m_maze.setWall(1, 3, WALL_SOUTH);
    m_maze.setWall(2, 3, WALL_SOUTH);
    m_maze.setWall(2, 2, WALL_EAST);
    m_maze.setWall(2, 1, WALL_EAST);
    m_maze.setWall(3, 0, WALL_EAST);
    m_maze.setWall(4, 1, WALL_EAST);
    m_maze.setWall(4, 2, WALL_EAST);
    m_maze.setWall(4, 3, WALL_EAST);
    m_maze.setWall(4, 4, WALL_EAST);
    m_maze.setWall(5, 5, WALL_SOUTH);
    m_maze.setWall(6, 5, WALL_SOUTH);
    m_maze.setWall(6, 6, WALL_EAST);

    // Kiểm thử tính năng lưu và nạp lại mê cung từ file
    if (m_maze.saveToFile("maps/maze01.txt"))
    {
        m_maze.loadFromFile("maps/maze01.txt");
    }
}

void Simulator::runSimulation(AlgorithmType algo)
{
    m_robot.reset(m_maze.getStart(), Direction::NORTH);

    std::string algoName = "Flood Fill";
    if (algo == AlgorithmType::BFS) algoName = "BFS";
    if (algo == AlgorithmType::DFS) algoName = "DFS";

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<Point> path = m_solver.solve(m_maze, m_robot.getPosition(), algo);
    auto t2 = std::chrono::high_resolution_clock::now();

    double elapsedMs = std::chrono::duration<double, std::milli>(t2 - t1).count();

    for (size_t i = 1; i < path.size(); ++i)
    {
        m_robot.moveTo(path[i]);
    }

    if (!path.empty() && m_maze.isGoal(m_robot.getPosition()))
    {
        m_robot.setState(RobotState::REACHED_GOAL);
    }
    else
    {
        m_robot.setState(RobotState::STUCK);
    }

    SimulationStats stats{
        algoName,
        m_robot.getState() == RobotState::REACHED_GOAL,
        path.empty() ? 0 : static_cast<int>(path.size()) - 1,
        elapsedMs
    };

    m_renderer.render(m_maze, m_robot, path);
    m_renderer.renderRobotStatus(m_robot, m_sensor.read(m_maze, m_robot));
    m_renderer.renderStats(stats);
}