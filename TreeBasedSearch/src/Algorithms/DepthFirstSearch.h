#pragma once

#include "SearchAlgorithm.h"

class DepthFirstSearch : public SearchAlgorithm {

public:
    std::vector<StepType>* Search(Grid&) override;

private:
    std::pair<Coord, std::map<Coord, Coord>>* TraceSteps(Grid&);

};
