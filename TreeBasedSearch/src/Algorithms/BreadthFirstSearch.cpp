#include "BreadthFirstSearch.h"

#include <iostream>
#include <queue>
#include <map>

std::pair<Coord, std::map<Coord, Coord>>* BreadthFirstSearch::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.GetAgentPosition();

    std::queue<Coord> queue;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    queue.push(agentPosition);
    explored.push_back(agentPosition);

    while (!queue.empty()) {

        Coord current = queue.front();
        queue.pop();

        for (Coord node : grid.GetNeighboringEmptyCoords(current)) {
            if (!vector_contains(explored, node)) {
                queue.push(node);
                explored.push_back(node);
                stepTrace.insert({ node, current });
                if (grid.IsGoalPosition(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
