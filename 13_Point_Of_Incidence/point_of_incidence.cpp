/*
    Advent of Code 2023 - 13.12.2023

    Link to the problem: https://adventofcode.com/2023/day/13
    
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
            inputData += "\n";
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
    nrows ++;   // We must apply this correction
}

// Function to fill in the grid
void fillGrid(std::vector<std::vector<char>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j] = input[strCounter];
            strCounter ++;
        }
    }
}

int findHorizontalReflexes(std::vector<std::vector<char>> grid, int currentIndex){

    // Base case: we ran out of rows
    /*
    if(currentRow.empty())
        return possibleReflexion ? rowIndex : 0;   // If variable possible reflexion is still true, then we have a reflection
     */

    // Take the current row and the next one
    std::vector<char> currentRow = grid[currentIndex];
    std::vector<char> nextRow = grid[currentIndex + 1];

    // Check if they are equal
    if(currentRow.size() == nextRow.size()){
        bool equalRows = true;
        for(int i = 0; i < currentRow.size(); i++){
            if(currentRow[i] != nextRow[i]){
                equalRows = false;
                break;
            }
        }
    }

    // If they are equal, start the recursion with the adjacent rows. If not, call the algorithm with currentIndex + 1
    
}

int main(){

    /*
    Brief approach that will be followed:
        - Read the input and automatically save the blocks in 2d vectors. The number of rows and cols must be guessed automatically. I might create a vector of 2d vectors, storing like that all the blocks
        - Once I can manipulate the blocks, the first naive approach is to take all the rows/cols and start comparing them with the adjacent ones. If we find a coincidence, then jump back to the previous/next row/col to check if there is a mirror --> Might implement a recursive function
        - That should be it :) Then finding the number of upper rows and left cols should be trivial. Should be lol with recursive functions nothing is trivial
    */

   // Store the example and the input in variables
    std::string example = "#.##..##.\n..#.##.#.\n##......#\n##......#\n..#.##.#.\n..##..##.\n#.#.##.#.\n\n#...##..#\n#....#..#\n..##..###\n#####.##.\n#####.##.\n..##..###\n#....#..#\n";
    std::string input = readInputText("input.txt");

    // Just to work with example. Might comment out
    //input = example;

    // Separate every block and store it in a vector. Still string, not grid
    std::vector<std::string> blocksVector = split(input, "\n\n");

    // Big loop
    for(auto block: blocksVector){

        // Guess the size of the grid
        int nrows = 0, ncols = 0;
        getGridDimensions(block, nrows, ncols);

        // Define the grid and fill it
        std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols)); // 2D vector with all the grid
        fillGrid(grid, block);

        // Find the mirrors :)
        
        /*
            I don't know whether I should define a function that finds both vertical and horizontal reflexes, or just 
            horizontal ones (easier to manipulate) and then repeat the algorithm with the transponed 2d vector. Must think
            of that.
        */



    }


    return 0;
}