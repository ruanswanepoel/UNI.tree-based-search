#include "BreadthFirstSearch.h"

#include <iostream>
#include <queue>
#include <map>


std::vector<StepType>* BreadthFirstSearch::Search(Grid& grid) {

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

std::pair<Coord, std::map<Coord, Coord>>* BreadthFirstSearch::TraceSteps(Grid& grid) {

    Coord agentPosition = grid.get_agent_position();

    std::queue<Coord> queue;
    std::vector<Coord> explored;
    std::map<Coord, Coord> stepTrace;

    queue.push(agentPosition);
    explored.push_back(agentPosition);

    while (!queue.empty()) {

        Coord current = queue.front();
        queue.pop();

        for (Coord node : grid.get_movable_coords(current)) {
            if (!vector_contains(explored, node)) {
                queue.push(node);
                explored.push_back(node);
                stepTrace.insert({ node, current });
                if (grid.is_goal_position(node))
                    return new std::pair<Coord, std::map<Coord, Coord>>(node, stepTrace);
            }
        }

    }

    return nullptr;

}
