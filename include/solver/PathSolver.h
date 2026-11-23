#ifndef PATH_SOLVER_H
#define PATH_SOLVER_H

#include <vector>
#include "maze/Maze.h"

enum class AlgorithmType
{
    BFS,
    DFS,
    FLOOD_FILL
};

class PathSolver
{
public:
    std::vector<Point> solve(const Maze& maze, Point start, AlgorithmType algo) const;

private:
    std::vector<Point> solveBFS(const Maze& maze, Point start) const;
    std::vector<Point> solveDFS(const Maze& maze, Point start) const;
    std::vector<Point> solveFloodFill(const Maze& maze, Point start) const;
    std::vector<Point> getAccessibleNeighbors(const Maze& maze, Point p) const;
};

#endif