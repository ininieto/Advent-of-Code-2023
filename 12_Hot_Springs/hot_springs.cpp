/*
    Advent of Code 2023 - 12.12.2023

    Link to the problem: https://adventofcode.com/2023/day/12

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

// Function to fill in a int vector given a string
std::vector<int> fillInVector(std::string str){

    std::vector<std::string> strVector = split(str, ",");
    std::vector<int> numVector;

    for(std::string strNum: strVector){
        numVector.push_back(stoull(strNum));
    }

    return numVector;
}


int main(){

    // Store the example and the input in variables
    std::string example = "???.### 1,1,3\n.??..??...?##. 1,1,3\n?#?#?#?#?#?#?#? 1,3,1,6\n????.#...#... 4,1,1\n????.######..#####. 1,6,5\n?###???????? 3,2,1\n";
    std::string input = readInputText("input.txt");
    
    // Just to work with example
    input = example;

    // Split the initial input by lines
    std::vector<std::string> splittedInput = split(input, "\n");

    // Read every line
    for(std::string line: splittedInput){

        // Separate the springs and the numbers
        std::string spring = line.substr(0, line.find(' '));
        std::string strNumbers = line.substr(line.find(' ') + 1);

        // Store the numbers in a vector
        std::vector<int> numbers = fillInVector(strNumbers);
        
        // Identify the ?? regions



    }







    return 0;
}