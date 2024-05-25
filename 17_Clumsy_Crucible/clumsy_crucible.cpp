/*
    Advent of Code 2023 - 16.12.2023

    Link to the problem: https://adventofcode.com/2023/day/16
    
    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

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
            std::cout << element.tile;
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

            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].tile = input[strCounter];
            strCounter ++;
        }
    }
}

// Structure that will replace the coordinates being a std::pair
struct coords{
    int x;
    int y;
};

int main(){

    /*
        Initial approach:

        I think I am gonna reutilize the code for 12.12 AOC22 (Hill Climbing: C:\Users\ininieto\Desktop\programacion\C++\Advent of Code 2022\12_Hill_Climbing)

        The idea is similar: treat the numbers as Node and go traversing the graph with the dijkstra algorithm. One problem that I found the other time was to implement
        the function in a recursive way. For low amount of nodes this might work, but it rapidly tends to overload. A better approach is to use queues. 

        Also, I will make a modification: the coordinates, instead of std::pair, will be a self-made struct with x and y members.
        This improves the readability
    
        Let's goooo
    */

   // Read the input data and example
    std::string example = "2413432311323\n3215453535623\n3255245654254\n3446585845452\n4546657867536\n1438598798454\n4457876987766\n3637877979653\n4654967986887\n4564679986453\n1224686865563\n2546548887735\n4322674655533\n";
    std::string inputData = readInputText("input.txt");
    inputData = example;    // Comment for real problem, uncomment for example

    // Store all the input in a grid
    int nrows, ncols;
    getGridDimensions(inputData, nrows, ncols);
     std::vector<std::vector <int>> grid(nrows, std::vector<int>(ncols));

    std::cout << example << '\n';

    return 0;
}