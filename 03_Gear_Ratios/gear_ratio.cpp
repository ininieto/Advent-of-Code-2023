/*
    Advent of Code 2023 - 03.12.2023

    Link to the problem: https://adventofcode.com/2023/day/3

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Number{

    std::pair<int, int> firstDigitPosition;
    int value;
    bool checked = false;
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
            inputData += "\n";
        }
    }
    return inputData;
}

// This function will ONLY return the position of the adjacent elements. Won't perform any further calculation
std::vector<std::pair<int, int>> getSurroundings(std::pair<int, int> position, int nrows, int ncols){

    std::vector<std::pair<int, int>> surroundings;

    std::pair<int, int> up = std::make_pair(position.first - 1, position.second);
    std::pair<int, int> down = std::make_pair(position.first + 1, position.second);
    std::pair<int, int> left = std::make_pair(position.first, position.second - 1);
    std::pair<int, int> right = std::make_pair(position.first, position.second + 1);
    std::pair<int, int> upLeft = std::make_pair(position.first - 1, position.second - 1);
    std::pair<int, int> upRight = std::make_pair(position.first - 1, position.second + 1);
    std::pair<int, int> downLeft = std::make_pair(position.first + 1, position.second - 1);
    std::pair<int, int> downRight = std::make_pair(position.first + 1, position.second + 1);

    if(position == std::make_pair(0, 0)){   // Top left corner
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
        surroundings.push_back(downRight);
    }
    else if(position == std::make_pair(0, ncols - 1)){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down);
        surroundings.push_back(downLeft); 
    }
    else if(position == std::make_pair(nrows - 1, 0)){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
        surroundings.push_back(upRight);
    }
    else if(position == std::make_pair(nrows - 1, ncols - 1)){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(upLeft);
    }
    else if(position.first == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
        surroundings.push_back(downLeft); 
        surroundings.push_back(downRight); 
    }
    else if(position.first == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up);  
        surroundings.push_back(upLeft); 
        surroundings.push_back(upRight);
    }
    else if(position.second == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down);  
        surroundings.push_back(upRight); 
        surroundings.push_back(downRight);
    }
    else if(position.second == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down);  
        surroundings.push_back(upLeft); 
        surroundings.push_back(downLeft);
    }
    else{   // No weird cases
        surroundings.push_back(right); 
        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
        surroundings.push_back(upRight); 
        surroundings.push_back(upLeft); 
        surroundings.push_back(downRight); 
        surroundings.push_back(downLeft); 
    }
    return surroundings;
}

// Function that checks the adjacent numbers to the symbol
void checkSurroundings(std::vector<std::vector<char>> grid, std::vector<std::pair<int, int>> surroundings){

    // Get all the surrounding values
    for(auto pos: surroundings){
        std::cout << grid[pos.first][pos.second] << ' ';
    }
    std::cout << '\n';



}

// Function to store all the numbers of the grid in a hashmap. This way we don't sum the same number more than once
void readAllNumbers(std::vector<std::string> splittedInput, std::vector<Number> &allNumbers){

    int nrows = splittedInput.size(), ncols = splittedInput[0].size();

    for(int i = 0; i < nrows; i++){
        std::string row = splittedInput[i];
        std::string strNum;
        bool firstDigit = true; // This will indicate if the digit read is the first of the number -> Must store its position
        Number num;

        for(int j = 0; j < ncols; j++){
            char c = row[j];
            if(isdigit(c)){
                strNum.push_back(c);
                if(firstDigit){
                    num.firstDigitPosition = std::make_pair(i, j);
                    firstDigit = false;
                }
            }
            else{
                if(strNum.length() > 0){
                    num.value = stoi(strNum);
                    allNumbers.push_back(num);
                    firstDigit = true;
                    strNum.clear();
                }
            }
        }
    }
}


int main(){

    std::string example = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
    std::string inputData = readInputText("input.txt");

    // Split the data
    std::vector<std::string> splittedExample = split(example, "\n");
    //std::vector<std::string> splittedInput = split(example, "\n");
    std::vector<std::string> splittedInput = splittedExample;
    
    // Store the data in a grid
    int nrows = splittedInput.size(), ncols = splittedInput[0].size();
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));

    // Store the data in a grid
    int i = 0;
    for(auto &row: grid){
        for(auto &element: row){
            if(example[i] == '\n') i++;
            element = example[i];
            i++;
        }
    }

    // Save all the numbers in an array. They belong to a struct with its position and whether they're checked or not
    std::vector<Number> allNumbers;
    readAllNumbers(splittedInput, allNumbers);

   // Read the grid looking for symbols. If found, check surroundings
    for (int i = 0; i < nrows; i++){
        std::string row = splittedInput[i];
        for (int j = 0; j < ncols; j++){
            char c = row[j];
            if (!isdigit(c) && c != '.'){ // Symbol detected
                std::pair<int, int> position = std::make_pair(i, j);
                std::vector<std::pair<int, int>> surroundings = getSurroundings(position, nrows, ncols);
                checkSurroundings(grid, surroundings);
            }
        }
    }

    return 0;
}
