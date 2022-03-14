#pragma once

#include "Algorithms/SearchAlgorithm.h"
//#include "Algorithms/DepthFirstSearch.h"
#include "Algorithms/BreadthFirstSearch.h"
//#include "Algorithms/GreedyBestFirst.h"
//#include "Algorithms/AStar.h"

class SearchAlgorithmFactory {

public:
    static SearchAlgorithm* Create(const char*);

};
