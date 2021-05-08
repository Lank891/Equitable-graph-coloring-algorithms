#include "equitable.h"
#include "colorings.h"
#include <iostream>

void FJK(Graph &graph) {
    while(!isEquitableColored(graph)) {
        auto most_common_color = getMostCommonColor(graph);
        auto least_common_color = getLeastCommonColor(graph);

        auto most_common_color_nodes = getNodesWithColor(graph, most_common_color.first);

        bool recolored = false;
        //If any of nodes with most common color can be recolored do that
        for(Node *node : most_common_color_nodes) {
            if(checkIfColorIsValid(graph, *node, least_common_color.first)) {
                node->color = least_common_color.first;
                recolored = true;
                std::cout << "Recolored " << node->id << " to " << node->color << "\n";
                break;
            }
        }
        //Else add new color
        if(!recolored) {
            int newColor = getLowestNotUsedColor(graph);
            most_common_color_nodes.at(0)->color = newColor;
            std::cout << "Added to " << most_common_color_nodes.at(0)->id << " color " << most_common_color_nodes.at(0)->color << "\n";
        }
    }
}

void MFJK(Graph &graph) {
    //TODO
    graph = graph;
}

bool isEquitableColored(const Graph &graph) {
    auto most_common_color = getMostCommonColor(graph);
    auto least_common_color = getLeastCommonColor(graph);

    return abs(most_common_color.second - least_common_color.second) <= 1;
}