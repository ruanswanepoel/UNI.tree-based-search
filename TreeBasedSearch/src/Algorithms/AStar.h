#pragma once

#include "SearchAlgorithm.h"

class AStar : public SearchAlgorithm {

private:
    std::pair<Coord, std::map<Coord, Coord>>* TraceSteps(Grid&) override;

};
