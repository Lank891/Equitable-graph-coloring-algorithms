#include "colorings.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>

void greedyColoring(Graph &graph)
{
    for (Node &node : graph)
    {
        node.color = getLowestValidColor(graph, node);
    }
}

void SLFColoring(Graph &graph)
{
    int maxSat = 0;
    std::vector<int> Ids;
    
    //First Color nodes with maximum degrees which can be colord only by first color
    for (Node &node : graph)
    {
        int length = getNeighbours(graph, node).size();

        if (maxDegree(graph) == length)
        {
            if (getLowestValidColor(graph, node) != FIRST_COLOR)
            {
                continue;
            }
            else
            {
                node.color = getLowestValidColor(graph, node);
            }
        }
    }

    //Then we color based on maximum saturation degree
    while (!checkIfFullColored(graph))
    {
        // get max saturation degree
        maxSat = getMaxSaturationDegree(graph);
        
        //check for every node if they have max saturation degree 
        //and if are not neighbours then color them with same color
        for (const Node &node : graph)
        {
            int count = 0;
            int n = getNeighbours(graph, node).size();
            if (getSaturationDegree(graph, node) == maxSat)
            {

                for (auto i : getNeighbours(graph, node))
                {
                    if (std::find(Ids.begin(), Ids.end(), i->id) != Ids.end())
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    };
                }
            }
            if (n == count)
            {
                Ids.emplace_back(node.id);
            }

            for (Node &node_ : graph)
            {
                if (std::find(Ids.begin(), Ids.end(), node_.id) == Ids.end())
                {
                    node_.color = getLowestValidColor(graph, node_);
                }
                else
                    continue;
            }

            Ids.clear();
        }
    }
}

int getLowestValidColor(const Graph &graph, const Node &node)
{
    auto neighbours = getNeighbours(graph, node);
    std::vector<int> neighbourColors;

    for (const Node *const neighbour : neighbours)
    {
        neighbourColors.emplace_back(neighbour->color);
    }

    std::vector<int>::iterator searchResult;
    int lowestColor = FIRST_COLOR - 1;

    do
    {
        lowestColor++;
        searchResult = std::find(neighbourColors.begin(), neighbourColors.end(), lowestColor);
    } while (searchResult != neighbourColors.end());

    return lowestColor;
}

int getLowestNotUsedColor(const Graph &graph)
{
    std::map<int, int> colors;
    for (const Node &node : graph)
    {
        colors[node.color]++;
    }

    int actualColor = FIRST_COLOR;

    while (colors[actualColor] > 0)
    {
        actualColor++;
    }

    return actualColor;
}

bool checkIfColorIsValid(const Graph &graph, const Node &node, color_t color)
{
    auto neighbours = getNeighbours(graph, node);

    return std::find_if(
               neighbours.begin(),
               neighbours.end(),
               [color](const Node *node) {
                   return node->color == color;
               }) == neighbours.end();
}

std::map<int, int> getColors(const Graph &graph)
{
    std::map<int, int> colors;
    for (const Node &node : graph)
    {
        colors[node.color]++;
    }
    return colors;
}

int numberOfUsedColors(const Graph &graph)
{
    auto colors = getColors(graph);
    int used_colors = 0;

    for (const auto color : colors)
    {
        if (color.second > 0)
        {
            used_colors++;
        }
    }

    return used_colors;
}

std::pair<color_t, color_count_t> getLeastCommonColor(const Graph &graph)
{
    auto colors = getColors(graph);

    int least_common_color = NO_COLOR;
    int least_common_freq = INT_MAX;

    for (const auto color : colors)
    {
        if (color.second <= least_common_freq)
        {
            least_common_freq = color.second;
            least_common_color = color.first;
        }
    }

    return std::make_pair<>(least_common_color, least_common_freq);
}

std::pair<color_t, color_count_t> getMostCommonColor(const Graph &graph)
{
    auto colors = getColors(graph);

    int most_common_color = NO_COLOR;
    int most_common_freq = INT_MIN;

    for (const auto color : colors)
    {
        if (color.second >= most_common_freq)
        {
            most_common_freq = color.second;
            most_common_color = color.first;
        }
    }

    return std::make_pair<>(most_common_color, most_common_freq);
}

std::vector<Node *> getNodesWithColor(Graph &graph, color_t color)
{
    std::vector<Node *> nodes;

    for (Node &node : graph)
    {
        if (node.color == color)
        {
            nodes.emplace_back(&node);
        }
    }

    return nodes;
}



int getSaturationDegree(const Graph &graph, const Node &node)
{
    std::vector<Node *> nodes;

    std::vector<int> satDegree;

    if (node.color == NO_COLOR)
    {
        if (node.neighbours.size() > 0)
        {
            for (auto node_n : getNeighbours(graph, node))
            {
                if (node_n->color != NO_COLOR && std::find(satDegree.begin(), satDegree.end(), node_n->color) == satDegree.end())
                {
                    satDegree.emplace_back(node_n->color);
                }
            }
        }
        else
            return 0;
    }
    else
        return -1;
    return satDegree.size();
}

int getMaxSaturationDegree(const Graph &graph)
{
    int max = 0;

    for (const Node &node_g : graph)
    {
        if (max < getSaturationDegree(graph, node_g))
        {
            max = getSaturationDegree(graph, node_g);
        }
    }
    return max;
}

bool checkIfFullColored(const Graph &graph)
{

    for (const Node &node : graph)
    {
        if (node.color == NO_COLOR)
        {
            return false;
        }
    }
    return true;
}

