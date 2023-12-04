/*
    Advent of Code 2023 - 01.12.2023

    Link to the problem: https://adventofcode.com/2023/day/1

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

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

std::string reverse(std::string str){

    std::string reversed;

    for(int i = str.length() - 1; i >= 0; i--) reversed.push_back(str[i]);
    return reversed;
}

int main(){

    std::string example = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen";
    std::string inputData = readInputText("input.txt");

    std::unordered_map<std::string, char> numberConversion = {{"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(inputData, "\n");

    int result = 0;

    for(std::string line: splittedInput){

        // Obtain the numbers
        std::string num;
        std::string writtenNum;

        for(int i = 0; i < line.length(); i++){
            if(isdigit(line[i])){
                num.push_back(line[i]);
                break;
            }
            else{   
                // Add character to a string in case there is a number written
                writtenNum.push_back(line[i]);

                // Check if a written number is inside the string
                for(auto w: numberConversion){
                    std::size_t found = writtenNum.find(w.first);
                    if(found != std::string::npos){
                        num.push_back(w.second);
                        break;
                    }
                }
                if(num.length() > 0) break;
            }
        }

        writtenNum.clear();
        
        for(int i = line.length() - 1; i >= 0; i--){
            if(isdigit(line[i])){
                num.push_back(line[i]);
                break;
            }
            else{   
                // Add character to a string in case there is a number written
                writtenNum.push_back(line[i]);

                // Check if a written number is inside the string
                for(auto w: numberConversion){
                    std::size_t found = reverse(writtenNum).find(w.first);
                    if(found != std::string::npos){
                        num.push_back(w.second);
                        break;
                    }
                }
                if(num.length() > 1) break;
            }
        }
        result += stoi(num);
    }

    std::cout << "The result is " << result << '\n';
    return 0;
}