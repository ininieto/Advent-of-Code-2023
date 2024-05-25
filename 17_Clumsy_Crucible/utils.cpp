#include <iostream>
#include <vector>
#include <fstream>

#include "Node.h"

// Function to split a std::string by a specific delimitator
std::vector<std::string> split(std::string text, std::string delim){

    std::vector<std::string> splittedText;
    size_t pos = 0;
    std::string token;

    while((pos = text.find(delim)) != std::string::npos){
        token = text.substr(0, pos);
        splittedText.push_back(token);
        text.erase(0, pos + delim.length());
    }

    if(text.length() > 0)
        splittedText.push_back(text);

    return splittedText;
}

// Read input data from txt file
std::string readInputText(std::string inputText){

    std::fstream inputfile;
    std::string inputData;

    inputfile.open(inputText, std::ios::in);
    if (inputfile.is_open()){
        std::string tp;

        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += '\n';
        }
    }
    return inputData;
}

// Function to get automatically the number of rows and columns
void getGridDimensions(std::string input, int &nrows, int &ncols){

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '\n' && ncols == 0)
            ncols = i;
        if(input[i] == '\n' && ncols > 0)
            nrows ++;
    }
}

// Function to print the whole grid. Debug purposes
void printGrid(std::vector<std::vector<Node>> &grid){
    for(const auto &row: grid){
        for(const auto &element: row){
            std::cout << element.getHeatLoss();
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void fillGrid(std::vector<std::vector<Node>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j].setY(i);
            grid[i][j].setX(j);
            grid[i][j].setHeatLoss(static_cast<int>(input[strCounter]) - 48);
            strCounter ++;
        }
    }
}
