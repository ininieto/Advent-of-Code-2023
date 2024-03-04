/*
    Advent of Code 2023 - 14.12.2023

    Link to the problem: https://adventofcode.com/2023/day/14
    
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
}

// Function to fill in the grid
void fillGrid(std::vector<std::vector<char>> &rows, std::vector<std::vector<char>> &cols, std::string input){

    int nrows = rows.size(), ncols = rows[0].size();

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            rows[i][j] = input[strCounter];
            cols[j][i] = input[strCounter];
            strCounter ++;
        }
    }
}

// Function to print the whole grid. Debug purposes
void printGrid(std::vector<std::vector<char>> grid){
    for(auto row: grid){
        for(auto element: row){
            std::cout << element;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Recursive function to tilt the lever to the north / west
void tiltRowColNorthWest(std::vector<char> &line, int &currentIndex){

    char &currentChar = line[currentIndex];
    char &prevChar = line[currentIndex - 1];

    // Base case: If first character
    if(currentIndex == 0){
        currentIndex ++;
        return tiltRowColNorthWest(line, currentIndex);
    }

    // Base case: if we can't keep going 
    if(currentIndex == line.size())
        return;

    // Inspect the current char. If it is an O, try to make it slide
    if(currentChar == 'O' && prevChar == '.'){
        prevChar = 'O';
        currentChar = '.';
        currentIndex --;    // If the rock could slide one position, maybe it can slide more
    }
    else
        currentIndex ++;

    // Repeat the algorithm for the next position
    return tiltRowColNorthWest(line, currentIndex);
}

// Recursive function to tilt the lever to the south / east
void tiltRowColSouthEast(std::vector<char> &line, int &currentIndex){

    char &currentChar = line[currentIndex];
    char &prevChar = line[currentIndex + 1];

    // Base case: If first character
    if(currentIndex == line.size() - 1){
        currentIndex --;
        return tiltRowColSouthEast(line, currentIndex);
    }

    // Base case: if we can't keep going 
    if(currentIndex == -1)
        return;

    // Inspect the current char. If it is an O, try to make it slide
    if(currentChar == 'O' && prevChar == '.'){
        prevChar = 'O';
        currentChar = '.';
        currentIndex ++;    // If the rock could slide one position, maybe it can slide more
    }
    else
        currentIndex --;

    // Repeat the algorithm for the next position
    return tiltRowColSouthEast(line, currentIndex);
}

// Function that tilts the platform to the north / west
void tiltPlatformNorthWest(std::vector<std::vector<char>> &lines){

    for (auto &line : lines){

        // We start in the second position, as we cannot slide out of bounds
        int startingIndex = 1;

        // Tilt this row / column
        tiltRowColNorthWest(line, startingIndex);
    }
}

// Function that tilts the platform to the south / east
void tiltPlatformSouthEast(std::vector<std::vector<char>> &lines){

    for (auto &line : lines){

        // We start in the penultimate position, as we cannot slide out of bounds
        int startingIndex = line.size() - 2;

        // Tilt this row / column
        tiltRowColSouthEast(line, startingIndex);
    }
}

int main(){

    // Save the example and the input in variables
    std::string example = "O....#....\nO.OO#....#\n.....##...\nOO.#O....O\n.O.....O#.\nO.#..O.#.#\n..O..#O..O\n.......O..\n#....###..\n#OO..#....\n";
    std::string input = readInputText("input.txt");

    // Debug
    input = example;

    // Split the input and store each line in a vector
    std::vector<std::string> splittedInput = split(input, "\n");

    // Store all the information in a grid
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);
    
    std::vector<std::vector<char>> rows(nrows, std::vector<char>(ncols)); // 2D vector for the rows
    std::vector<std::vector<char>> cols(nrows, std::vector<char>(ncols)); // 2D vector for the rows
    fillGrid(rows, cols, input);

    /*
        Now we need to encapsulate this process of tilting every column in a function tiltNorth()
        Then we can call, inside a loop, tiltNorth(), tiltWest(), tiltSouth(), tiltEast()
        We need to define functions to convert rows <-> columns
    */

    for(uint64_t i = 0; i < 1; i++){

       // Take the columns and tilt north
       tiltPlatformNorthWest(cols);
       
       // TODO: Create a rows vector based on the cols

       // Tilt the rows west
       tiltPlatformNorthWest(rows);

       // TODO: Create a cols vector based on the rows

       // Tilt the cols south

       // Tilt the cols south
       tiltPlatformSouthEast(cols);

       // TODO: Create a rows vector based on the cols

       // Till the rows east
       tiltPlatformSouthEast(rows);

       // TODO: Create a cols vector based on the rows

    }

    // Now we need to calculate the total load
    uint64_t totalLoad = 0;

    for(auto col: cols){

        // Iterate through the columns
        for(int i = 0; i < cols.size(); i++){
            if(col[i] == 'O')
                totalLoad += (col.size() - i);  // The first row must count col.size() (10 in example), then 9, then 8...
        }        
    }

    // Debug
    printGrid(cols);

    // Print the result
    std::cout << "The result is " << totalLoad << '\n';

    return 0;
}