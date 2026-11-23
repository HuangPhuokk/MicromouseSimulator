#ifndef APPLICATION_H
#define APPLICATION_H

#include "maze/Maze.h"

class Application
{
public:
    void initialize();
    void run();
    void shutdown();

private:
    Maze m_maze;
};

#endif