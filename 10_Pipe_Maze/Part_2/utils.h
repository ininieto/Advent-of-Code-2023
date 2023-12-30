#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

#include "Pipe.h"

std::vector<std::string> split(std::string text, std::string delim);
std::string readInputText(std::string inputText);
void getGridDimensions(std::string input, int &nrows, int &ncols);
std::vector<std::pair<int, int>> getSurroundings(Pipe currentPipe, int nrows, int ncols);
bool possibleJump(Pipe currentPipe, Pipe nextPipe);
void addNextJump(std::vector<Pipe*> &nextJumps, Pipe* nextJump);
void printGrid(std::vector<std::vector<Pipe>> grid);
void drawLoopInGrid(std::vector<std::vector<Pipe>> &grid);

#endif