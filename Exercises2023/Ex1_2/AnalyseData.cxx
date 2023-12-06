// Fani Henry
// 15 Nov 2023
// SUPA C++ course - Lab 1

/* Update: I've started writing the straightLine function in the 
CustomFunction.cxx file. It's not properly adding all the values though... 

Note that the *backup* version of this script is just what I had before 
splitting the 2 functions => keep as backup
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "CustomFunctions.h"

int main(){
    
    // read the data
    std::string fileName = "input2D_float.txt";
    reading(fileName);

    // use the terminal input to define whether to print or calculate the magnitude
    std::string answer;
    std::cout << "Would you like to use the printing or calculating function? Answer with 'P' or 'C'." << std::endl;
    std::cin >> answer;

    if (answer=="P"){
        int lineNumber;
        std::string answer2;
        std::cout << "How many lines would you like to print?" << std::endl;
        std::cin >> answer2;
        lineNumber = std::stoi(answer2);
        printing(lineNumber);
        }
    else if (answer=="C"){magnitudeFct();}
    else {std::cout << "Please type your answer in the format P or C.";}
    
    // reading the error files 
    std::string fileName2 = "error2D_float.txt";
    reading_error(fileName2);

    // computing the best fit equation
    straightLine();

    // computing the power function x^y
    //float x = 2.0;
    //float y = 3;

    //float result = power(x, y);

    //std::cout << x << " raised to the power of " << y << " is: " << result << std::endl;

    return 0;
}
