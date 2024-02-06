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
void expandSpace(std::vector<std::vector<char>> &grid, std::vector<int> &rowsExpansionIndexes, std::vector<int> &colsExpansionIndexes, int expansionRate){

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
            //grid.insert(grid.begin() + i, row); // If we are here is precisely because our row was empty :)
            rowsExpansionIndexes.push_back(i);
            i += expansionRate; // Increase the iteration index
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
            /*for(int j = 0; j < grid.size(); j++){   // Insert a '.' in every row in the i position
                grid[j].insert(grid[j].begin() + i, '.');
            }*/
            colsExpansionIndexes.push_back(i);
            i += expansionRate; // Increase the iteration index
        }
    }
}


// Function to find all the galaxies in the grid and save the coordinates
std::vector<std::pair<uint64_t, uint64_t>> getGalaxiesCoords(std::vector<std::vector<char>> grid){

    std::vector<std::pair<uint64_t, uint64_t>> galaxiesCoords;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '#')
                galaxiesCoords.push_back(std::make_pair(i, j));
        }
    }

    return galaxiesCoords;
}

// Function to apply the increase of expansion
void correctExpansion(std::vector<std::pair<uint64_t, uint64_t>> &galaxiesCoords, std::vector<int> rowsExpansionIndexes, std::vector<int> colsExpansionIndexes, int expansionRate){

    for(std::pair<uint64_t, uint64_t> &coord: galaxiesCoords){

        int numCorrections = 0;

        // Correction on rows
        for(int rowIndex: rowsExpansionIndexes)
            if(coord.first > rowIndex)  
                numCorrections ++;
            else    break;
        
        coord.first += numCorrections * expansionRate;

        numCorrections = 0; // Reset the number of corrections

        // Correction on columns
        for(int colIndex: colsExpansionIndexes)
            if(coord.second > colIndex) numCorrections ++;
            else break;

        coord.second +=  numCorrections * expansionRate;
    }
}


// Function to compute the Manhattan distance
int manhattanDist(std::pair<uint64_t, uint64_t> coords1, std::pair<uint64_t, uint64_t> coords2){

    return abs(coords2.first - coords1.first) + abs(coords2.second - coords1.second);
}

int main(){

    // Define the input
    std::string example = "...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....\n";
    std::string input = readInputText("input.txt");

    // Get the number of rows and columns
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);

    // Define the grid and fill it
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols)); // 2D vector with all the grid
    fillGrid(grid, input);

    // Perform the space expansion
    int expansionRate = 1;
    std::vector<int> rowsExpansionIndexes;  // Array that contains the indexes of the rows that must be expanded
    std::vector<int> colsExpansionIndexes;  // Array that contains the indexes of the cols that must be expanded
    expandSpace(grid, rowsExpansionIndexes, colsExpansionIndexes, expansionRate);

    // As we can only jump up, down, left and right, we are dealing with MANHATTAN DISTANCES
    // The general formula to compute this distance is |x2 - x1| + |y2 - y1|

    // Vector that contains the coordinates of all the galaxies
    std::vector<std::pair<uint64_t, uint64_t>> galaxiesCoords = getGalaxiesCoords(grid);
    uint64_t result = 0;

    // Apply corrections on the coordinates --> Longer expansion
    correctExpansion(galaxiesCoords, rowsExpansionIndexes, colsExpansionIndexes, expansionRate);

    // Calculate all the distances
    for(int i = 0; i < galaxiesCoords.size(); i++){
        for(int j = i + 1; j < galaxiesCoords.size(); j++)
            result += manhattanDist(galaxiesCoords[i], galaxiesCoords[j]);
    }


    // I got an answer of 1986903970 but it is too low :( all the tests were OK
    // Set variables to uint64_t and got 611872260002 but still too low :(
    // When trying to replicate the first part I am getting 9483730 instead of 9556896

    std::cout << static_cast<uint64_t>(result) << '\n';

    return 0;
}