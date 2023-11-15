// Fani Henry - 15/11/2023
// Test code for SUPA C++ course 

#include <iostream>
#include <cmath>

// function which is defined later 
float magnitudeFct();

int main(){
    
    // Task 1
    std::cout << "Hello World!" << std::endl;

    // Task 2
    /*
    float x = 2.3;
    float y = 4.5;
    float magnitude = sqrt(pow(x,2) + pow(y,2));
    std::cout << "The magnitude of the vector is " << magnitude << std::endl;
    */

    // Task 3
    float myMagnitude = magnitudeFct();

    return 0;
}

float magnitudeFct(){
    float x;
    float y;
    std::cout << "What is the value of x?" << std::endl;
    std::cin >> x;
    std::cout << "What is the value of y?" << std::endl;
    std::cin >> y;
    float magnitude = sqrt(pow(x,2) + pow(y,2));
    std::cout << "The magnitude of the vector is " << magnitude << std::endl;
    return magnitude;
    
}