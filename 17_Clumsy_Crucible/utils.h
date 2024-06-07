#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

#include "Node.h"

std::vector<std::string> split(std::string text, std::string delim);
std::string readInputText(std::string inputText);
void getGridDimensions(std::string input, int &nrows, int &ncols);
void printGrid(std::vector<std::vector<Node>> &grid);
void fillGrid(std::vector<std::vector<Node>> &grid, std::string input);
bool isInBounds(int x, int y, std::vector<std::vector<Node>> &grid);
void getLeftAndRightPositions(coords position, coords direction, coords &leftPosition, coords &rightPosition);
void insertNodeInNextNodesVector(std::vector<Node*> &nextNodesVector, Node* node);

#endif // UTILS_H