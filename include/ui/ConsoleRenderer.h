#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include <vector>
#include "maze/Maze.h"
#include "robot/Robot.h"
#include "sensor/WallSensor.h"
#include "stats/Statistics.h"

class ConsoleRenderer
{
public:
    void render(const Maze& maze, const Robot& robot, const std::vector<Point>& path) const;
    void renderRobotStatus(const Robot& robot, const SensorReading& reading) const;
    void renderStats(const SimulationStats& stats) const;
};

#endif