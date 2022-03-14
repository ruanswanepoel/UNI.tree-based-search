#include "SearchAlgorithmFactory.h"

#include <string>

SearchAlgorithm* SearchAlgorithmFactory::Create(const char* algStr) {

    if (strcmp(algStr, "dfs") == 0)
        return new BreadthFirstSearch();
    else if (strcmp(algStr, "bfs") == 0)
        return new BreadthFirstSearch();
    else if (strcmp(algStr, "gbf") == 0)
        return new BreadthFirstSearch();
    else if (strcmp(algStr, "astar") == 0)
        return new BreadthFirstSearch();

    return nullptr;

}
