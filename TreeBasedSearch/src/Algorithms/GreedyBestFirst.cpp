#include "GreedyBestFirst.h"

Coord GetBest(std::vector<Coord>& list, std::vector<Coord>& goalPositions) {

    int index = 0;
    int minDistance = INT_MAX;

    for (size_t i = 0; i < list.size(); i++) {
        Coord curr = list[i];
        int currClosest = INT_MAX;
        for (Coord c : goalPositions) {
            int dist = curr.Distance(c);
            currClosest = (dist < currClosest) ? dist : currClosest;
        }
        if (currClosest < minDistance) {
            minDistance = currClosest;
            index = i;
        }
    }

    Coord result = list[index];
    list.erase(list.begin() + index);
    return result;

}

std::pair<Coord, std::map<Coord, Coord>>* GreedyBestFirstAlgorithm::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.GetAgentPosition();

    std::vector<Coord> list;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    list.push_back(agentPosition);
    explored.push_back(agentPosition);

    while (!list.empty()) {

        Coord current = GetBest(list, grid.GetGoalPositions());

        for (Coord node : grid.GetNeighboringEmptyCoords(current)) {
            if (!vector_contains(explored, node)) {
                list.push_back(node);
                explored.push_back(node);
                stepTrace.insert({ node, current });
                if (grid.IsGoalPosition(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
