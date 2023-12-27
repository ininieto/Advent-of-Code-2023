#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

#include "Pipe.h"

std::vector<std::string> split(std::string text, std::string delim);
std::string readInputText(std::string inputText);
std::vector<std::pair<int, int>> getSurroundings(Pipe currentPipe, int nrows, int ncols);

#endif