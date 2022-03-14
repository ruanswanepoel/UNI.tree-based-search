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
 search <filename>             Displays the map defined in <filename>
 search <filename> <method>    Performs the tree search denoted by <method> for the map defined in <filename>

Available Methods:
 DFS     Depth First Search
 BFS     Breadth First Search
 GBFS    Greedy Best First
 AS      A Star
)""";


const char* stepTypeToString(StepType st) {

    if (st == StepType::Up)
        return "Up";
    else if (st == StepType::Left)
        return "Left";
    else if (st == StepType::Down)
        return "Down";
    return "Right";

}

int main(int argc, char** argv) {

    // Check if arguments are valid
    if (argc != 2 && argc != 3) {
        std::cout << "Error: Bad number of arguments\n" << std::endl;
        std::cout << USAGE_MSG << std::endl;
        exit(1);
    }

    std::string filename = argv[1];
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
    grid.load(lines);

    // Display command
    if (argc == 2) {
        std::vector<std::string> gridString = grid.to_string();
        for (std::string s : gridString)
            std::cout << s << std::endl;
        std::cout << std::endl;
        return 0;
    }

    // Process search algorithm
    std::string method = argv[2];
    for (char& c : method) c = toupper(c);

    SearchAlgorithm* alg = AlgorithmFactory::Create(method);

    // Check if method is valid
    if (alg == nullptr) {
        std::cout << "Error: '" << method << "' is not a valid search method.\n" << std::endl;
        std::cout << USAGE_MSG << std::endl;
        exit(1);
    }

    // Perform the search
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

    return 0;

}
