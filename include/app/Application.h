#ifndef APPLICATION_H
#define APPLICATION_H

#include "simulation/Simulator.h"

class Application
{
public:
    void initialize();
    void run();
    void shutdown();

private:
    Simulator m_simulator;
};

#endif