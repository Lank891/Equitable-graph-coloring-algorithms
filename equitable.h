#pragma once
#include "graph.h"


/**
 * Takes a colored and recolors it using FJK coloring
 * 
 * @param graph Graph that will be recolored, will be modified
 */ 
void FJK(Graph &graph);
/**
 * Takes a colored and recolors it using Modified FJK (MFJK) coloring
 * 
 * @param graph Graph that will be recolored, will be modified
 */ 
void MFJK(Graph &graph);

/**
 * Checks if graph is colored in an equitable way
 * 
 * @param graph Graph to check
 * @returns True if actual coloring is equitable, False otherwise
 */
bool isEquitableColored(const Graph &graph);
