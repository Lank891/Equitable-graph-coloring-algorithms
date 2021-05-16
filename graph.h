#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

///Integer representing color
typedef int color_t;

///Constant representing the lack of color
const color_t NO_COLOR = -1;
///Constant representing first color
const color_t FIRST_COLOR = 1;

///Struct that represents node (vertex) in a graph. Consists of id, color and vector of ids of neighbours.
struct Node {
    int id;
    color_t color;
    std::vector<int> neighbours;

    Node(int _id, std::vector<int> _neighbours) {
        id = _id;
        neighbours = _neighbours;
        color = NO_COLOR;
    }
};

///Vector of nodes representing a graph
typedef std::vector<Node> Graph;

///Override of << to print a node to the ostream
std::ostream& operator<<(std::ostream &os, const Node &node);
///Override of << to print a graph to the ostream
std::ostream& operator<<(std::ostream &os, const Graph &graph);

/**
 * Gets neighbours of a node in a graph as pointers (non-editable)
 * 
 * @param graph Graph to check
 * @param node Node to find neighbours of
 * @returns Vector of pointers to non-editable nodes that are neighbours of given node in a graph
 */
std::vector<const Node*> getNeighbours(const Graph &graph, const Node &node);

/**
 * Creates a graph based on a input stream
 * 
 * @param inputStream input stream with the graph
 * @returns Graph created based on the stream
 */
Graph readFromStream(std::istream &inputStream);


/**
 * Get max degree of a Graph
 * 
 * @param graph Graph to check
 * @returns Maximum degree of graph
 */
int maxDegree(Graph &graph);

