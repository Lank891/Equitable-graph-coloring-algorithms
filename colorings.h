#pragma once
#include "graph.h"
#include <vector>
#include <utility>
#include <map>

/**
 * Takes a graph and colors it in a greedy way
 * 
 * @param graph Graph that will be colored, will be modified
 */ 
void greedyColoring(Graph &graph);
/**
 * Takes a graph and colors it using Saturation Largest-First algorithm
 * 
 * @param graph Graph that will be colored, will be modified
 */ 
void SLFColoring(Graph &graph);

/**
 * Gets the lowest color that a node can be colored with to have proper coloring
 * 
 * @param graph Graph that the node is in
 * @param node Node that we want to find color for
 * @returns The lowest color such that coloring will be proper if node is colored using it
 */
int getLowestValidColor(const Graph &graph, const Node &node);
/**
 * Finds the lowest not used color in the whole graph
 * 
 * @param graph Graph to check
 * @returns lowest not used color
 */
int getLowestNotUsedColor(const Graph &graph);
/**
 * Checks if color will be valid for a node in a given graph
 * 
 * @param graph Graph that the node is in
 * @param node Node to check
 * @param color Color to check
 * @returns True if node can be colored with given color, False otherwise
 */
bool checkIfColorIsValid(const Graph &graph, const Node &node, color_t color);

///Integer representing number of nodes with given color
typedef int color_count_t;

/**
 * Gets all the colors from a graph with the amount of each
 * 
 * @param graph Graph to check
 * @returns Map with keys being colors and values being their amounts
 */
std::map<color_t, color_count_t> getColors(const Graph &graph);
/**
 * Gets number of colors in given graph
 * 
 * @param graph Graph to check
 * @returns Number of colors in the graph
 */
int numberOfUsedColors(const Graph &graph);

/**
 * Gets least common color in a graph together with the amount nodes colored with it
 * 
 * @param graph Graph to check
 * @returns Pair with first value being the least common color and second value being the amount of it
 */
std::pair<color_t, color_count_t> getLeastCommonColor(const Graph &graph);
/**
 * Gets most common color in a graph together with the amount nodes colored with it
 * 
 * @param graph Graph to check
 * @returns Pair with first value being the most common color and second value being the amount of it
 */
std::pair<color_t, color_count_t> getMostCommonColor(const Graph &graph);

/**
 * Gets nodes of a given color from a graph
 * 
 * @param graph Graph to check
 * @param color Color to check
 * @returns Vector of pointers to nodes (editable) with wanted color
 */
std::vector<Node*> getNodesWithColor(Graph &graph, color_t color);