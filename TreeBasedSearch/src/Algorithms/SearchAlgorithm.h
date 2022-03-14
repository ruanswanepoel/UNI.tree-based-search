#pragma once

#include "../Helpers.h"
#include "../Coord.h"
#include "../StepType.h"
#include "../Grid.h"

class SearchAlgorithm {

public:
    virtual std::vector<StepType>* Search(Grid&) = 0;

};
