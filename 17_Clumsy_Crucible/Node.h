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
    struct Path{
        std::stack<Node *> prevNodes;  // Succession of Nodes that the lava has followed to reach the current Node
        int distance = __INT_MAX__;    // Total amount of heat loss of the whole Path
        int countStraightSteps = 0;    // Number of consecutive straight steps that the lava has followed
    };

    // Constructors
    Node();
    Node(int x, int y);

    // Getters
    coords getCoords() const;
    int getHeatLoss() const;
    std::vector<Path> getPaths() const;

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);

    // Modify the Path of a Node
    void addprevNodeToPath(Node* prevNode, int pathId);
    void setDistance(int dist, int pathId);
    void setCountStraightSteps(int numSteps, int pathId);

private:

    int heatLoss = -1;
    coords pos;
    std::vector<Path> paths;    // We need a vector, as there are multiple Paths to reach a Node
};

#endif  // NODE_H