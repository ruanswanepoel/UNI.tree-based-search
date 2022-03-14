#include "DepthFirstSearch.h"

#include <vector>
#include <stack>

std::vector<StepType>* DepthFirstSearch::Search(Grid& grid) {

    std::vector<StepType>* result = new std::vector<StepType>();

    Coord agentPosition = grid.get_agent_position();
    std::pair<Coord, std::map<Coord, Coord>>* traceResult = TraceSteps(grid);

    if (traceResult == nullptr)
        return nullptr;

    Coord curr = traceResult->first;
    std::map<Coord, Coord> stepTrace = traceResult->second;

    while (curr != agentPosition) {
        Coord prev = stepTrace.at(curr);
        StepType step;
        // TODO: implement the following [getStepDirection] in grid
        if (curr.Row() < prev.Row())
            step = StepType::Up;
        else if (curr.Row() > prev.Row())
            step = StepType::Down;
        else if (curr.Col() < prev.Col())
            step = StepType::Left;
        else if (curr.Col() > prev.Col())
            step = StepType::Right;
        // //
        result->insert(result->begin(), step);
        curr = prev;
    }

    return result;

}

std::pair<Coord, std::map<Coord, Coord>>* DepthFirstSearch::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.get_agent_position();

    std::stack<Coord> stack;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    stack.push(agentPosition);
    explored.push_back(agentPosition);

    while (!stack.empty()) {

        Coord current = stack.top();
        stack.pop();

        for (Coord node : grid.get_movable_coords(current)) {
            if (!vector_contains(explored, node)) {
                stack.push(node);
                explored.push_back(node);
                stepTrace.insert({ node, current });
                if (grid.is_goal_position(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
