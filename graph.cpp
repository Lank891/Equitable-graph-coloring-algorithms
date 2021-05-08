#include "graph.h"
#include <algorithm>
#include <sstream>
#include <iterator>

std::ostream& operator<< (std::ostream &os, const Node &node) {
    os << "Id: " << node.id << "; Color: " << node.color << '\n';
    os << "\tNeighbours: ";
    for(const int n : node.neighbours) {
        os << n << " ";
    } 
    os << '\n';
    return os;
}

std::ostream& operator<<(std::ostream &os, const Graph &graph) {
    for(const Node& node : graph) {
        os << node;
    }
    return os;
}

std::vector<const Node*> getNeighbours(const Graph &graph, const Node &node) {
    std::vector<const Node*> neighbours;

    for(const Node& g_node : graph) {
        if(std::find(node.neighbours.begin(), node.neighbours.end(), g_node.id) != node.neighbours.end()) {
            neighbours.emplace_back(&g_node);
        }
    }

    return neighbours;
}

Graph readFromStream(std::istream &inputStream) {
    Graph g;

    std::string line;
    while(getline(inputStream, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens {
            std::istream_iterator<std::string>(iss), {}
        };

        int id = std::stoi(tokens.at(0));
        std::vector<int> neighbours;
        for(size_t i = 1; i < tokens.size(); i++) {
            neighbours.emplace_back(std::stoi(tokens.at(i)));
        }

        Node n(id, neighbours);
        g.emplace_back(n);
    }

    return g;
}