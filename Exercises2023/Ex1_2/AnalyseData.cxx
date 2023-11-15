// Fani Henry
// 15 Nov 2023
// SUPA C++ course - Lab 1

#include <iostream>
#include <fstream>
#include <cmath>

int main(){

    // open and read the file
    std::string fileName = "input2D_float.txt";
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line 
    std::string line;  
    int lineNumber = 0;
    while(std::getline(inputFile,line)){
        std::cout << line << std::endl;
        lineNumber++;
        std::cout << lineNumber;
    }

    return 0;
}

