#include "AStar.h"

struct NodeScore {
    int g, h, f;
    NodeScore() : g(0), h(0), f(0) {}
    NodeScore(int _g, int _h) {
        g = _g;
        h = _h;
        f = g + h;
    }
    bool operator< (const NodeScore& other) const {
        if (f < other.f)
            return true;
        else if (f < other.f)
            return true;
        return false;
    }
};

Coord GetBest(std::vector<Coord>& open, std::map<Coord, NodeScore>& nodeScores) {

    int index = 0;
    NodeScore best = NodeScore(INT_MAX, INT_MAX);

    for (size_t i = 0; i < open.size(); i++) {
        if (nodeScores[open[i]] < best) {
            index = i;
            best = nodeScores[open[i]];
        }
    }

    Coord result = open[index];
    open.erase(open.begin() + index);

    return result;

}

int GetDistanceToClosestGoal(Coord coord, std::vector<Coord>& goalPositions) {

    int minDist = INT_MAX;

    for (Coord c : goalPositions) {
        int d = coord.Distance(c);
        minDist = (d < minDist) ? d : minDist;
    }

    return minDist;

}


std::pair<Coord, std::map<Coord, Coord>>* AStar::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.GetAgentPosition();

    std::vector<Coord> open;
    std::vector<Coord> closed;
    std::map<Coord, NodeScore> nodeScores;
    std::map<Coord, Coord> stepTrace;

    open.push_back(agentPosition);
    nodeScores[agentPosition] = NodeScore(0, GetDistanceToClosestGoal(agentPosition, grid.GetGoalPositions()));

    while (!open.empty()) {

        Coord current = GetBest(open, nodeScores);
        NodeScore currScore = nodeScores[current];
        closed.push_back(current);

        for (Coord node : grid.GetNeighboringEmptyCoords(current)) {
            NodeScore score = NodeScore(currScore.g + 1, GetDistanceToClosestGoal(node, grid.GetGoalPositions()));
            if (!vector_contains(closed, node) || score.f < currScore.f) {
                open.push_back(node);
                nodeScores.insert({ node, score });
                stepTrace.insert({ node, current });
                if (grid.IsGoalPosition(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
