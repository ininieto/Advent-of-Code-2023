/*
    Advent of Code 2023 - 06.12.2023

    Link to the problem: https://adventofcode.com/2023/day/6

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <vector>

int main(){
    
    std::vector<int> timeVec = {7, 15, 30};
    std::vector<int> distVec = {9, 40, 200};
    
    int result = 1;
    
    for(int i = 0; i < timeVec.size(); i++){
        
        int currentTime = timeVec[i];
        int currentDist = distVec[i];
        
        int possibleHoldTimes = 0;
        
        for(int holdTime = 0; holdTime <= currentTime; holdTime++){
            
            
            int speed = holdTime;
            int traveledDist = speed * (currentTime - holdTime);
            
            if(traveledDist > currentDist)
                possibleHoldTimes ++;
            else if(traveledDist < currentDist && possibleHoldTimes > 0)
                break;
        }
        
        result *= possibleHoldTimes;
    }
    
    std::cout << "The result is " << result << "\n";

    return 0;
}