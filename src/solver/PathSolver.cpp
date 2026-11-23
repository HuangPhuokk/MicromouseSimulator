#include "solver/PathSolver.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <array>

std::vector<Point> PathSolver::getAccessibleNeighbors(const Maze& maze, Point p) const
{
    std::vector<Point> neighbors;
    if (!maze.hasWall(p.x, p.y, WALL_NORTH) && p.y + 1 < Maze::SIZE) neighbors.push_back({p.x, p.y + 1});
    if (!maze.hasWall(p.x, p.y, WALL_EAST)  && p.x + 1 < Maze::SIZE) neighbors.push_back({p.x + 1, p.y});
    if (!maze.hasWall(p.x, p.y, WALL_SOUTH) && p.y - 1 >= 0)         neighbors.push_back({p.x, p.y - 1});
    if (!maze.hasWall(p.x, p.y, WALL_WEST)  && p.x - 1 >= 0)         neighbors.push_back({p.x - 1, p.y});
    return neighbors;
}

std::vector<Point> PathSolver::solve(const Maze& maze, Point start, AlgorithmType algo) const
{
    switch (algo)
    {
        case AlgorithmType::BFS:        return solveBFS(maze, start);
        case AlgorithmType::DFS:        return solveDFS(maze, start);
        case AlgorithmType::FLOOD_FILL: return solveFloodFill(maze, start);
    }
    return {};
}

std::vector<Point> PathSolver::solveBFS(const Maze& maze, Point start) const
{
    std::array<std::array<bool, Maze::SIZE>, Maze::SIZE> visited{};
    std::array<std::array<Point, Maze::SIZE>, Maze::SIZE> parent{};
    std::queue<Point> q;

    visited[start.y][start.x] = true;
    q.push(start);

    Point foundGoal{-1, -1};
    while (!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if (maze.isGoal(curr))
        {
            foundGoal = curr;
            break;
        }

        for (Point next : getAccessibleNeighbors(maze, curr))
        {
            if (!visited[next.y][next.x])
            {
                visited[next.y][next.x] = true;
                parent[next.y][next.x] = curr;
                q.push(next);
            }
        }
    }

    std::vector<Point> path;
    if (foundGoal.x == -1) return path;

    for (Point at = foundGoal; !(at == start); at = parent[at.y][at.x])
    {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Point> PathSolver::solveDFS(const Maze& maze, Point start) const
{
    std::array<std::array<bool, Maze::SIZE>, Maze::SIZE> visited{};
    std::array<std::array<Point, Maze::SIZE>, Maze::SIZE> parent{};
    std::stack<Point> st;

    st.push(start);
    visited[start.y][start.x] = true;

    Point foundGoal{-1, -1};
    while (!st.empty())
    {
        Point curr = st.top();
        st.pop();

        if (maze.isGoal(curr))
        {
            foundGoal = curr;
            break;
        }

        for (Point next : getAccessibleNeighbors(maze, curr))
        {
            if (!visited[next.y][next.x])
            {
                visited[next.y][next.x] = true;
                parent[next.y][next.x] = curr;
                st.push(next);
            }
        }
    }

    std::vector<Point> path;
    if (foundGoal.x == -1) return path;

    for (Point at = foundGoal; !(at == start); at = parent[at.y][at.x])
    {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Point> PathSolver::solveFloodFill(const Maze& maze, Point start) const
{
    std::array<std::array<int, Maze::SIZE>, Maze::SIZE> dist;
    for (auto& row : dist) row.fill(255);

    std::queue<Point> q;
    for (Point g : maze.getGoals())
    {
        dist[g.y][g.x] = 0;
        q.push(g);
    }

    while (!q.empty())
    {
        Point curr = q.front();
        q.pop();

        for (Point next : getAccessibleNeighbors(maze, curr))
        {
            if (dist[next.y][next.x] > dist[curr.y][curr.x] + 1)
            {
                dist[next.y][next.x] = dist[curr.y][curr.x] + 1;
                q.push(next);
            }
        }
    }

    std::vector<Point> path;
    if (dist[start.y][start.x] == 255) return path;

    Point curr = start;
    path.push_back(curr);
    while (!maze.isGoal(curr))
    {
        Point bestNext = curr;
        int minDist = dist[curr.y][curr.x];

        for (Point next : getAccessibleNeighbors(maze, curr))
        {
            if (dist[next.y][next.x] < minDist)
            {
                minDist = dist[next.y][next.x];
                bestNext = next;
            }
        }

        if (bestNext == curr) break;
        curr = bestNext;
        path.push_back(curr);
    }
    return path;
}