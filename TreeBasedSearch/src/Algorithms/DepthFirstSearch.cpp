#include "DepthFirstSearch.h"

#include <vector>
#include <stack>

std::pair<Coord, std::map<Coord, Coord>>* DepthFirstSearch::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.GetAgentPosition();

    std::stack<Coord> stack;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    stack.push(agentPosition);
    explored.push_back(agentPosition);

    while (!stack.empty()) {

        Coord current = stack.top();
        stack.pop();

        for (Coord node : grid.GetNeighboringEmptyCoords(current)) {
            if (!vector_contains(explored, node)) {
                stack.push(node);
                explored.push_back(node);
                stepTrace.insert({ node, current });
                if (grid.IsGoalPosition(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
