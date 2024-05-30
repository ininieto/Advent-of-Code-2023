#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#pragma once
#include <vector>
#include "Node.h"

// Struct that enables the priority queue to order the Node* by its minDistance -> min_heap
struct SmallestDistanceFirst{
    bool operator()(Node* const& n1, Node* const& n2){
        return n1->getMinDistance() > n2->getMinDistance();
    }
};

std::vector<Node*> getNextJumps(Node* currentNode, Node* prevNode, std::vector<std::vector <Node>> &grid);
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols);

#endif  // DIJKSTRA_H