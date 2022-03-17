#pragma once

#include "Algorithms/SearchAlgorithm.h"
#include "Algorithms/DepthFirstSearch.h"
#include "Algorithms/BreadthFirstSearch.h"
#include "Algorithms/GreedyBestFirst.h"
#include "Algorithms/AStar.h"

class AlgorithmFactory {

public:
    static SearchAlgorithm* Create(std::string algStr) {
        if (algStr == "DFS")
            return new DepthFirstSearch();
        else if (algStr == "BFS")
            return new BreadthFirstSearch();
        else if (algStr == "GBFS")
            return new GreedyBestFirstAlgorithm();
        else if (algStr == "AS")
            return new AStar();
        return nullptr;
    }

};
