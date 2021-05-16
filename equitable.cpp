#include "equitable.h"
#include "colorings.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

void FJK(Graph &graph)
{
    while (!isEquitableColored(graph))
    {
        auto most_common_color = getMostCommonColor(graph);
        auto least_common_color = getLeastCommonColor(graph);

        auto most_common_color_nodes = getNodesWithColor(graph, most_common_color.first);

        bool recolored = false;
        //If any of nodes with most common color can be recolored do that
        for (Node *node : most_common_color_nodes)
        {
            if (checkIfColorIsValid(graph, *node, least_common_color.first))
            {
                node->color = least_common_color.first;
                recolored = true;
                std::cout << "Recolored " << node->id << " to " << node->color << "\n";
                break;
            }
        }
        //Else add new color
        if (!recolored)
        {
            int new_color = getLowestNotUsedColor(graph);
            most_common_color_nodes.at(0)->color = new_color;
            std::cout << "Added to " << most_common_color_nodes.at(0)->id << " color " << new_color << "\n";
        }
    }
}

void MFJK(Graph &graph)
{
    color_t one_before_last_common_color = NO_COLOR;
    color_t last_most_common_color = NO_COLOR;
    while (!isEquitableColored(graph))
    {
        auto colors = getColorsOrderedByFrequency(graph);
        
        color_t most_common_color = colors.back().first;

        bool recolored = false;

        //Check for infinite loop of recolors
        if(most_common_color != one_before_last_common_color) {
            for(auto &color : colors) {
                auto nodes_to_recolor = getNodesWithColor(graph, most_common_color);

                //If next color to consider is more or the same frequent then color we want to get rid of - stop
                if((int)nodes_to_recolor.size() <= color.second) {
                    break;
                }

                //Recolor one of the vertices into considered color
                for (Node *node : nodes_to_recolor)
                {
                    if (checkIfColorIsValid(graph, *node, color.first))
                    {
                        node->color = color.first;
                        recolored = true;
                        std::cout << "Recolored " << node->id << " to " << node->color << "\n";
                        break;
                    }
                }
            }
        }

        //Add new color if no recolorings occured
        if (!recolored)
        {
            auto node_to_recolor = getNodesWithColor(graph, most_common_color).at(0);
            int new_color = getLowestNotUsedColor(graph);
            node_to_recolor->color = new_color;
            std::cout << "Added to " << node_to_recolor->id << " color " << new_color << "\n";
        }

        one_before_last_common_color = last_most_common_color;
        last_most_common_color = most_common_color;
    }
}

bool isEquitableColored(const Graph &graph)
{
    auto most_common_color = getMostCommonColor(graph);
    auto least_common_color = getLeastCommonColor(graph);

    return abs(most_common_color.second - least_common_color.second) <= 1;
}