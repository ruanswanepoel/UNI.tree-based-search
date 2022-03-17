#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "StepType.h"
#include "Coord.h"
#include "Helpers.h"
#include "Grid.h"
#include "AlgorithmFactory.h"

constexpr const char* USAGE_MSG = R"""(Usage:
 search <filename>                     Displays the map defined in <filename>.
 search <filename> <method>            Performs the tree search denoted by <method> for the map defined in <filename>.
 search <filename> <method> display    Performs the tree search and displays the map with the resulting path.

Available Methods:
 DFS     Depth First Search
 BFS     Breadth First Search
 GBFS    Greedy Best First
 AS      A Star
)""";


void err(const char* msg) {
    std::cout << "Error: " << msg << "\n\n" << USAGE_MSG << std::endl;
    exit(1);
}

int main(int argc, char** argv) {

    if (argc < 2 || argc > 4)
        err("Bad number of arguments");

    bool display = false;
    bool performSearch = false;
    std::string filename = argv[1];
    std::string method;

    // Whether to display the map
    if (argc == 2) {
        display = true;
    }
    else if (argc == 4) {
        if (strcmp(argv[3], "display"))
            err("Invalid 3rd argument.");
        display = true;
    }

    // Load search method
    if (argc >= 3) {
        performSearch = true;
        method = argv[2];
        for (char& c : method) c = toupper(c);
    }

    std::ifstream infile(filename);

    // Check if file exists
    if (!infile.good()) {
        std::cout << "Error: The file '" << filename << "' does not exist\n" << std::endl;
        exit(1);
    }

    // Load file content
    std::vector<std::string> lines;
    std::string buffer;
    while (std::getline(infile, buffer)) {
        lines.push_back(buffer);
    }

    // Load Grid object
    Grid grid = Grid();
    grid.Load(lines);

    // Perform the search
    if (performSearch) {

        SearchAlgorithm* alg = AlgorithmFactory::Create(method);
        if (alg == nullptr)
            err("Invalid search method.");

        std::vector<StepType>* steps = alg->Search(grid);

        // Check if solution is valid
        if (steps == nullptr) {
            std::cout << "No solution found.\n" << std::endl;
            return 0;
        }

        // Generate instruction string
        std::stringstream instructions;
        for (StepType el : *steps) {
            instructions << stepTypeToString(el) << "; ";
        }

        // Print result
        std::cout << filename << " " << method << " " << steps->size() << std::endl;
        std::cout << instructions.str() << "\n" << std::endl;

    }

    // Display the map
    if (display) {
        std::vector<std::string> gridString = grid.ToString();
        for (std::string s : gridString)
            std::cout << s << std::endl;
        std::cout << std::endl;
        return 0;
    }

    return 0;

}
