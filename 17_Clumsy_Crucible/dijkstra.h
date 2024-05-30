#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <vector>
#include "Node.h"

std::vector<Node*> getPossibleJumps(Node* currentNode, Node* prevNode, std::vector<std::vector <Node>> &grid);
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols);

#endif