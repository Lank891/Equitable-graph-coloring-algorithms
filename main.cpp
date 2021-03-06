/**
 * Created by Andrzej Litkowski and Nader Tavana for Chromatic Graph Theory (Summer 2021) classes
 * 
 * Compile: g++ -Wall -Wextra -Werror -std=c++17  "colorings.cpp" "equitable.cpp" "graph.cpp" "main.cpp" -o "equitable.exe"
 * 
 * Usage: ./equitable.exe "file-with-graph"
 * 
 * Graph file structure: each line contains numbers separated by spaces that represents one node - 
 *  first number is node number, the rest are its neighbours
 * 
 * File is not validated, so if graph or format are not valid in best case there will be an exception
 *  and in the worst one - there will be garbage results
 * 
 * Example files with graphs can be found in 'test-graphs' folder that should be provided alongside this code
 * 
 * Functions have no validation inside, so using it in an order that is illogical may provide garbage results
 *  (for example checking if graph is equitable colored without coloring it at first will result in true - there is only one 'NO_COLOR')
 */

#include "graph.h"
#include "colorings.h"
#include "equitable.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "One argument is needed - file with graph";
        return 1;
    }

    std::ifstream file(argv[1]);

    if(!file.is_open()) {
        std::cout << "File could not be opened";
        return 1;
    }

    Graph graphGreedyFJK = readFromStream(file);
    file.clear();
    file.seekg(0);
    Graph graphSLFFJK = readFromStream(file);
    file.clear();
    file.seekg(0);
    Graph graphGreedyMFJK = readFromStream(file);

    std::cout << "Graph found:\n" << graphGreedyFJK << "\n\n------\n\n";

    greedyColoring(graphGreedyFJK);
    greedyColoring(graphGreedyMFJK);
    SLFColoring(graphSLFFJK);

    
    std::cout << "Greedly coloured:\n" << graphGreedyFJK << "\nNumber of colors: " << numberOfUsedColors(graphGreedyFJK) << "\n\n------\n\n";

    std::cout << "SLF coloured:\n" << graphSLFFJK << "\nNumber of colors: " << numberOfUsedColors(graphSLFFJK) << "\n\n------\n\n";

    FJK(graphGreedyFJK);
    FJK(graphSLFFJK);
    MFJK(graphGreedyMFJK);
    
    std::cout << "Greedly to FJK coloured:\n" << graphGreedyFJK << "\nNumber of colors: " << numberOfUsedColors(graphGreedyFJK) << "\n\n------\n\n";
    std::cout << "SLF to FJK coloured:\n" << graphSLFFJK << "\nNumber of colors: " << numberOfUsedColors(graphSLFFJK) << "\n\n------\n\n";
    std::cout << "Greedly to MFJK coloured:\n" << graphGreedyMFJK << "\nNumber of colors: " << numberOfUsedColors(graphGreedyMFJK) << "\n\n------\n\n";

    return 0;
}