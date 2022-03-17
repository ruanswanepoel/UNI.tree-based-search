#pragma once

#include "SearchAlgorithm.h"

class GreedyBestFirstAlgorithm : public SearchAlgorithm {

private:
    std::pair<Coord, std::map<Coord, Coord>>* TraceSteps(Grid&) override;

};
