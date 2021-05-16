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
            int newColor = getLowestNotUsedColor(graph);
            most_common_color_nodes.at(0)->color = newColor;
            std::cout << "Added to " << most_common_color_nodes.at(0)->id << " color " << most_common_color_nodes.at(0)->color << "\n";
        }
    }
}

void MFJK(Graph &graph)
{
    while (!isEquitableColored(graph))
    {
        auto most_common_color = getMostCommonColor(graph);
        auto least_common_color = getLeastCommonColor(graph);

        auto most_common_color_nodes = getNodesWithColor(graph, most_common_color.first);

        auto colors = getColors(graph);
        bool recolored = false;

        for (Node *node : most_common_color_nodes)
        {

            //auto min = *std::min_element(colors.begin(), colors.end(),
            //[](const auto& l, const auto& r) { return l.second < r.second; });

            for (auto col : colors)
            {

                if (checkIfColorIsValid(graph, *node, col.first))
                {
                    node->color = col.first;
                    recolored = true;
                    std::cout << "Recolored " << node->id << " to " << node->color << "\n";
                    if (getNodesWithColor(graph, node->color).size() >= getNodesWithColor(graph, col.first).size())
                    {
                        break;
                    }
                }
            }
            //colors.erase(min.first);
        }

        if (!recolored)
        {
            int newColor = getLowestNotUsedColor(graph);
            most_common_color_nodes.at(0)->color = newColor;
            std::cout << "Added to " << most_common_color_nodes.at(0)->id << " color " << most_common_color_nodes.at(0)->color << "\n";
        }
    }
}

bool isEquitableColored(const Graph &graph)
{
    auto most_common_color = getMostCommonColor(graph);
    auto least_common_color = getLeastCommonColor(graph);

    return abs(most_common_color.second - least_common_color.second) <= 1;
}