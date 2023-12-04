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
    reading();

    // use the terminal input to define wheteher to print or calculate the magnitude
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

    straightLine();
    
    return 0;


}
