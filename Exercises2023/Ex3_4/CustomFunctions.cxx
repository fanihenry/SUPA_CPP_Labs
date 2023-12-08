// Definitions of functions for AnalyseData.cxx

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CustomFunctions.h"

//defining vectors outside the scope of the functions
std::vector<double> dataset;

//////////////////////////
/*

READING function

This function takes as the name of a file as argument, reads every every line and write the value of 
x and y into separate vectors. 

*/
//////////////////////////

std::vector<double> reading(std::string fileName){

    // open and read the file
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line and store the values in a vector
    std::string line;  
    int lineNumber = 0;
    double x;

    while(std::getline(inputFile,line)){
        std::string x_string = line.substr(0, line.find(","));
        x = std::stof(x_string);
        dataset.push_back(x);
        lineNumber++;}

    //closing the file
    inputFile.close();
    std::cout << "File is closed" << std::endl; //check-point

    return dataset;
}

