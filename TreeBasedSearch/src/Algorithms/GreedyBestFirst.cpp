#include "GreedyBestFirst.h"

std::pair<Coord, std::map<Coord, Coord>>* GreedyBestFirstAlgorithm::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.GetAgentPosition();

    std::vector<Coord> list;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    list.push_back(agentPosition);
    explored.push_back(agentPosition);

    return nullptr;

}
