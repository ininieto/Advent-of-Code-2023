#pragma once

#ifndef NODE_H
#define NODE_H

#include <vector>

// Structure that will replace the coordinates being a std::pair
struct coords{
    int x, y;
};

class Node{

public:
    struct History{
        std::vector<Node *> prevNodes;
        int distance;
    };

    // Constructors
    Node();
    Node(int x, int y);

    // Getters
    coords getCoords() const;
    int getHeatLoss() const;
    History getHistory() const;

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);

    // Modify history of a Node
    void addprevNode(Node* prevNode);
    void setDistance(int dist);

private:

    int heatLoss = -1;
    coords pos;
    History hist;   // The best way I found to track multiple paths. Every path will have its associated distance 
};

#endif  // NODE_H