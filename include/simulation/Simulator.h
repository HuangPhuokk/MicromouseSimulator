#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "maze/Maze.h"
#include "robot/Robot.h"
#include "sensor/WallSensor.h"
#include "solver/PathSolver.h"
#include "ui/ConsoleRenderer.h"
#include "stats/Statistics.h"

class Simulator
{
public:
    void setupSampleMaze();
    void runSimulation(AlgorithmType algo);

private:
    Maze m_maze;
    Robot m_robot;
    WallSensor m_sensor;
    PathSolver m_solver;
    ConsoleRenderer m_renderer;
};

#endif