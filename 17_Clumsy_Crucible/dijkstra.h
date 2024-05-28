#ifndef DIJKSTRA
#define DIJKSTRA

#pragma once
#include <vector>
#include "Node.h"

std::vector<coords> getSurroundings(Node* currentNode, int nrows, int ncols);
std::vector<coords> getPossibleJumps(Node* currentNode, std::vector<coords> surroundings, std::vector<std::vector <Node>> &grid);
// void checkIfNodeExists(Node* currentNode, Node* &targetNode, std::pair<int, int> targetPosition);
// int dijkstra(Node* startNode, Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition, int &numNodes);
void dijkstra();

#endif