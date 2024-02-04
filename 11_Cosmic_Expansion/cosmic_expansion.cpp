/*
    Advent of Code 2023 - 11.12.2023

    Link to the problem: https://adventofcode.com/2023/day/11

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

// Function to print the whole grid. Debug purposes
void printGrid(std::vector<std::vector<char>> grid){
    for(auto row: grid){
        for(auto element: row){
            std::cout << element;
        }
        std::cout << '\n';
    }
}

// Function to get automatically the number of rows and columns
void getGridDimensions(std::string input, int &nrows, int &ncols){

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '\n' && ncols == 0)
            ncols = i;
        if(input[i] == '\n' && ncols > 0)
            nrows ++;
    }
    //nrows ++;   // We must apply this correction
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

// Function that expands the space
void expandSpace(std::vector<std::vector<char>> &grid){

    // Expand rows
    for(int i = 0; i < grid.size(); i++){

        bool isRowEmpty = true;

        std::vector<char> row = grid[i];
        for(auto element: row){
            if(element == '#'){
                isRowEmpty = false;
                break;
            }
        }

        // If row is empty, insert another empty row
        if(isRowEmpty){
            std::vector emptyRow = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
            grid.insert(grid.begin() + i, emptyRow);
            i++; // Increase the iteration index
        }        
    }

    // Expand columns
    for(int i = 0; i < grid[0].size(); i++){

        std::vector<char> column;
        bool isColumnEmpty = true;

        // Fill the column
        for(int j = 0; j < grid.size(); j++)
            column.push_back(grid[j][i]);

        // If column is empty, expand it
        for(char c: column){
            if(c != '.')
                isColumnEmpty = false;
        }

        // If column is empty, insert another empty column
        if(isColumnEmpty){
            for(int j = 0; j < grid.size(); j++){   // Insert a . in every row in the i position
                grid[j].insert(grid[j].begin() + i, '.');
            }
            i++; // Increase the iteration index
        }
    }
}


// Function to find all the galaxies in the grid and save the coordinates
std::vector<std::pair<int, int>> getGalaxiesCoords(std::vector<std::vector<char>> grid){

    std::vector<std::pair<int, int>> galaxiesCoords;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '#')
                galaxiesCoords.push_back(std::make_pair(i, j));
        }
    }

    return galaxiesCoords;
}


int main(){

    // Define the input
    std::string example = "...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....\n";
    std::string input = readInputText("input.txt");

    // Get the number of rows and columns
    int nrows = 0, ncols = 0;
    getGridDimensions(example, nrows, ncols);

    // Define the grid and fill it
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols)); // 2D vector with all the grid
    fillGrid(grid, example);

    // Perform the space expansion
    expandSpace(grid);

    // As we can only jump up, down, left and right, we are dealing with MANHATTAN DISTANCES
    // The general formula to compute this distance is |x2 - x1| + |y2 - y1|

    // The approach will be: store the coordinates of all galaxies in a vector, then compute all 
    // the cross distances (must watch out and not compute the same distance twice e.g. 1 -> 2 and 2 -> 1)
    // Sum all those distances

    std::vector<std::pair<int, int>> galaxiesCoords = getGalaxiesCoords(grid);



    // Debug
    printGrid(grid);



    return 0;
}