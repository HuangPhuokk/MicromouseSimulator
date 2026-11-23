#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>

struct SimulationStats
{
    std::string algorithmName;
    bool goalReached = false;
    int stepCount = 0;
    double elapsedMs = 0.0;
};

#endif