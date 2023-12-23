/*
    Advent of Code 2023 - 10.12.2023

    Link to the problem: https://adventofcode.com/2023/day/10

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


int main(){

    /*
        - Read the input
        - Store every character in a grid
        - When doing so, find where the S is and save its position in startPosition
        - Then comes the algorithm
        - Scan all the adjacent characters (luckily no diagonal movement)
        - Define a function isPossibleConnection() to see if we can jump to a specific position
        - Still unsure about how to determine the distance. Maybe I could create a class Pipe with its 
          inherited subclasses (all the possible positions of the pipe) and with a member variable "distance"
          I find it a bit too over-engineering but could be a way to refresh subclasses    
    */



    return 0;
}