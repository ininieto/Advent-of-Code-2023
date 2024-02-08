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

// Function to find the regions that have no dots --> could be damaged
std::vector<std::string> findRegionsWithoutDot(std::string spring){

    std::vector<std::string> regionsWithoutDot;
    std::string temp;

    for(char c: spring){
        if(c != '.')
            temp.push_back(c);
        else{
            if(temp.size() == 0)    
                continue;
            regionsWithoutDot.push_back(temp);
            temp.clear();
        }
    }
    if(temp.size() > 0) regionsWithoutDot.push_back(temp);

    return regionsWithoutDot;
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
        
        // Identify the regions that have no '.'
        std::vector<std::string> regionsWithoutDot = findRegionsWithoutDot(spring);

        // Now I should look at the # and guess things with that

        /*
        
        First example: ???.###    1,1,3
            It is easier to start saying that there are already three # --> now I know that ??? correspond to 1, 1 --> 1 possibility
        
        Second example: .??..??...?##.   1,1,3
            As in the end I have two # and a ? it is obvious that there must be a # --> one possibility.
            Then I have two regions like ?? ?? and 1, 1 --> that leads to 4 possibilities (#. #.), (#. .#), (.# #.), (.# .#)
        
        Third example: ?#?#?#?#?#?#?#?   1,3,1,6

        */

       // I mean, brute force is always there :) I can always try all combinations for ? and see if it works

       // Actually, I feel that a safer approach would be first implementing brute-force, and if it doesn't run, try to think deeper 

       // I might have a hashmap alreadyTriedPatterns that prevents over-engineering, and also keeps track of the valid ones
       // Then, for every new pattern that is tried, a function checkPossiblePattern() would make sure if it's ok or not

       // How many possible patterns are there? --> Combinatory is our friend
       // In the first example, we want to distribute two # in 3 ? --> C(3, 2) = 3! / 2! (3 - 2)! = 3 
       // The formula involves factorials. Not sure if I should find an already defined function or do it myself (probably recursion)

       




    }







    return 0;
}