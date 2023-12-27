#pragma once

#ifndef PIPE_MAZE_H
#define PIPE_MAZE_H

#include <iostream>
#include <vector>

#include "Pipe.h"

void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, Pipe &startingPipe);
void pipeMaze(Pipe currentPipe, std::vector<std::vector<Pipe>> grid, std::vector<Pipe> nextJumps);

#endif