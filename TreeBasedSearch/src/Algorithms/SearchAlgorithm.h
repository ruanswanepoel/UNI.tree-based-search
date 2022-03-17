#pragma once

#include "../Helpers.h"
#include "../Coord.h"
#include "../StepType.h"
#include "../Grid.h"

class SearchAlgorithm {

public:
    std::vector<StepType>* Search(Grid&);

private:
    virtual std::pair<Coord, std::map<Coord, Coord>>* TraceSteps(Grid& grid) = 0;

};
