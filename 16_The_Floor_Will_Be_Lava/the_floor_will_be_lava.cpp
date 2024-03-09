/*
    Advent of Code 2023 - 16.12.2023

    Link to the problem: https://adventofcode.com/2023/day/16
    
    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

struct Node{

    int x, y;
    char tile;
    bool energized = false;

    // Default constructor
    Node(): x(-1), y(-1), tile('?') {}

    // Constructor with parameters
    Node(int x_p, int y_p, char tile_p): x(x_p), y(y_p), tile(tile_p) {}

};

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

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Node>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].tile = input[strCounter];
            strCounter ++;
        }
    }
}

int main(){

    // Read the input
    std::string example = readInputText("example.txt");
    std::string input = readInputText("input.txt");

    // Debug
    input = example;

    // I want to have a 2d grid of Nodes
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);

    std::vector<std::vector<Node>> grid(nrows, std::vector<Node>(ncols)); // 2D vector for the rows
    fillGrid(grid, input);

    std::cout << example << '\n';

    std::cout << input << '\n';


    return 0;
}