#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H

#include "maze/Maze.h"
#include "robot/Robot.h"

struct SensorReading
{
    bool front;
    bool left;
    bool right;
};

class WallSensor
{
public:
    SensorReading read(const Maze& maze, const Robot& robot) const;
};

#endif