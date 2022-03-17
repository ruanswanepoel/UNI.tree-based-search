#include "SearchAlgorithm.h"

std::vector<StepType>* SearchAlgorithm::Search(Grid& grid) {

    std::vector<StepType>* result = new std::vector<StepType>();

    Coord agentPosition = grid.GetAgentPosition();
    std::pair<Coord, std::map<Coord, Coord>>* traceResult = TraceSteps(grid);

    if (traceResult == nullptr)
        return nullptr;

    Coord curr = traceResult->first;
    std::map<Coord, Coord> stepTrace = traceResult->second;

    while (curr != agentPosition) {
        Coord prev = stepTrace.at(curr);
        result->insert(result->begin(), grid.GetStepDirection(prev, curr));
        grid.SetNodeAsPath(curr);
        curr = prev;
    }

    return result;

}
