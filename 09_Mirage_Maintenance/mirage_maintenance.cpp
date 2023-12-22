/*
    Advent of Code 2023 - 09.12.2023

    Link to the problem: https://adventofcode.com/2023/day/9

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

    std::vector<std::string> strVector = split(str, " ");
    std::vector<int> seedVector;

    for(std::string strNum: strVector){
        seedVector.push_back(stoull(strNum));
    }

    return seedVector;
}

// Simple function to sum all elements of a vector
int sumVector(std::vector<int> vec){

    int sum = 0;
    for(int e : vec)
        sum += e;
    
    return sum;
}

// Recursive function that obtains the differences between all the elements of the vector 
// Returns the number that must be added to the last element of the vector
int getDifferences(std::vector<int> originalNumbers){

    // Will store all the resultant vector in this array
    std::vector<int> differences;
    for(int i = 1; i < originalNumbers.size(); i++)
        differences.push_back(originalNumbers[i] - originalNumbers[i - 1]);

    if(sumVector(differences) == 0)
        return differences[differences.size() - 1];
    
    return differences[differences.size() - 1] + getDifferences(differences);
} 

int main(){

    std::string example = "0 3 6 9 12 15\n1 3 6 10 15 21\n10 13 16 21 30 45";
    std::string input = readInputText("input.txt");

    // Split the input
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(input, "\n");
    //std::vector<std::string> splittedInput = splittedExample;

    int finalResult = 0;

    // Read all the lines
    for(std::string line: splittedInput){

        std::vector<int> originalNumbers = fillInVector(line);

        // Call the recursive function for the vector
        int nextNum = originalNumbers[originalNumbers.size() - 1] + getDifferences(originalNumbers);
        finalResult += nextNum;
    }

    // Got a result of 1887980197 but I'm on a plane and I cannot prove it :)
    // It was right :)
    std::cout << "The result is " << finalResult << '\n';

    return 0;
}