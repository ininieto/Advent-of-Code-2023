/*
    Advent of Code 2023 - 01.12.2023

    Link to the problem: https://adventofcode.com/2023/day/1

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

    std::string example = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet";
    std::string inputData = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(inputData, "\n");

    int result = 0;

    for(std::string line: splittedInput){

        // Obtain the numbers
        std::string num;

        for(int i = 0; i < line.length(); i++){
            if(isdigit(line[i])){
                num.push_back(line[i]);
                break;
            }
        }
        
        for(int i = line.length() - 1; i >= 0; i--){
            if(isdigit(line[i])){
                num.push_back(line[i]);
                break;
            }
        }
        result += stoi(num);
    }

    std::cout << "The result is " << result << '\n';
    return 0;
}