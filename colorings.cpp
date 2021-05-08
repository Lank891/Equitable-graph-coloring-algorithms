#include "colorings.h"
#include <algorithm>
#include <climits>

void greedyColoring(Graph &graph) {
    for(Node& node : graph) {
        node.color = getLowestValidColor(graph, node);
    }
}

void SLFColoring(Graph &graph) {
    //Todo
    graph = graph;
}

int getLowestValidColor(const Graph &graph, const Node &node) {
    auto neighbours = getNeighbours(graph, node);
    std::vector<int> neighbourColors;

    for(const Node * const neighbour : neighbours) {
        neighbourColors.emplace_back(neighbour->color);
    }

    std::vector<int>::iterator searchResult;
    int lowestColor = FIRST_COLOR - 1;

    do {
        lowestColor++;
        searchResult = std::find(neighbourColors.begin(), neighbourColors.end(), lowestColor);
    } while(searchResult != neighbourColors.end());

    return lowestColor;
}

int getLowestNotUsedColor(const Graph &graph) {
    std::map<int, int> colors;
    for(const Node &node : graph) {
        colors[node.color]++;
    }

    int actualColor = FIRST_COLOR;

    while(colors[actualColor] > 0) {
        actualColor++;
    }

    return actualColor;
}

bool checkIfColorIsValid(const Graph &graph, const Node &node, color_t color) {
    auto neighbours = getNeighbours(graph, node);

    return std::find_if(
        neighbours.begin(), 
        neighbours.end(), 
        [color](const Node* node) {
            return node->color == color;
        }
    ) == neighbours.end();
}

std::map<int, int> getColors(const Graph &graph) {
    std::map<int, int> colors;
    for(const Node &node : graph) {
        colors[node.color]++;
    }
    return colors;
}

int numberOfUsedColors(const Graph &graph) {
    auto colors = getColors(graph);
    int used_colors = 0;

    for(const auto color : colors) {
        if(color.second > 0) {
            used_colors++;
        }
    }

    return used_colors;
}

std::pair<color_t, color_count_t> getLeastCommonColor(const Graph &graph) {
    auto colors = getColors(graph);

    int least_common_color = NO_COLOR;
    int least_common_freq = INT_MAX;

    for(const auto color : colors) {
        if(color.second <= least_common_freq) {
            least_common_freq = color.second;
            least_common_color = color.first;
        }
    }

    return std::make_pair<>(least_common_color, least_common_freq);
}

std::pair<color_t, color_count_t> getMostCommonColor(const Graph &graph) {
    auto colors = getColors(graph);

    int most_common_color = NO_COLOR;
    int most_common_freq = INT_MIN;

    for(const auto color : colors) {
        if(color.second >= most_common_freq) {
            most_common_freq = color.second;
            most_common_color = color.first;
        }
    }

    return std::make_pair<>(most_common_color, most_common_freq);
}

std::vector<Node*> getNodesWithColor(Graph &graph, color_t color) {
    std::vector<Node*> nodes;

    for(Node &node : graph) {
        if(node.color == color) {
            nodes.emplace_back(&node);
        }
    }

    return nodes;
}