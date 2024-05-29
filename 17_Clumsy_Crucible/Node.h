#pragma once

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <stack>

// Structure that will replace the coordinates being a std::pair
struct coords{
    int x, y;
};

class Node{

public:

    // Struct that keeps track of the path that lava is following
    struct History{
        std::vector<std::stack<Node *>> paths;  // There can be more than one way to reach a Node -> I call them path
        int distance = __INT_MAX__;
        int countStraightSteps = 0;
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
    void addprevNodeToPath(Node* prevNode, int pathId);
    void setDistance(int dist);

private:

    int heatLoss = -1;
    coords pos;
    History hist;   // The best way I found to track multiple paths. Every path will have its associated distance 
};

#endif  // NODE_H