// Definitions of functions for AnalyseData.cxx

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CustomFunctions.h"

// defining vectors outside the scope of the functions
std::vector<float> x_array;
std::vector<float> y_array;
std::vector<float> magnitude_array;
std::vector<float> gradient_array;
std::vector<float> intercept_array;
std::vector<float> sum_array;
std::vector<float> chi_array;
std::vector<float> error_x;
std::vector<float> error_y;
std::vector<float> xy_array;
std::vector<float> x2_array;
int amount=1;

//reading function 

int reading(std::string fileName){

    // open and read the file
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line and store the values in a vector
    std::string line;  
    int lineNumber = 0;
    double x, y;

    while(std::getline(inputFile,line)){
        if (lineNumber > 0) { //skipping the first line
            
            // add x coordinate to the vector
            std::string x_string = line.substr(0, line.find(","));
            x = std::stof(x_string);
            x_array.push_back(x);

            // add y coordinate to the vector
            std::string y_string = line.substr(line.find(",")+1, line.find("/n"));
            y = std::stof(y_string);
            y_array.push_back(y);

        }
        lineNumber++;
    }

    //closing the file
    inputFile.close();
    std::cout << "File is closed" << std::endl; //check-point
    return 0;
}


//reading function - FOR ERRORS

int reading_error(std::string fileName2){

    // open and read the file
    std::ifstream inputFile(fileName2);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line and store the values in a vector
    std::string line;  
    int lineNumber = 0;
    double x, y;

    while(std::getline(inputFile,line)){
        if (lineNumber > 0) { //skipping the first line
            
            // add x coordinate to the vector
            std::string x_string = line.substr(0, line.find(","));
            x = std::stof(x_string);
            error_x.push_back(x);

            // add y coordinate to the vector
            std::string y_string = line.substr(line.find(",")+1, line.find("/n"));
            y = std::stof(y_string);
            error_y.push_back(y);

        }
        lineNumber++;
    }

    // check-point
    std::cout << "The errors have been added to a vector" << std::endl;

    //closing the file
    inputFile.close();
    std::cout << "File is closed" << std::endl; //check-point
    return 0;
}


//printing function 

int printing(int lineNumber) {
    double x;
    double y;

    if (lineNumber>x_array.size()){
        std::cout << "It exceeds the maximum number of lines, which is " << x_array.size() <<std::endl;
        lineNumber = x_array.size();}

    for(int i=0; i<lineNumber; i++){

        //getting the coordinates
        x = x_array[i];
        y = y_array[i];

        //calculating the magnitude and printing the outcome
        float magnitude = sqrt(pow(x,2) + pow(y,2));
        std::cout << "For the point " << i << " with coordinates (" << x << "," << y << ")"<< ", the magnitude of the vector is " << magnitude << std::endl;
        magnitude_array.push_back(magnitude);}

    return 0;
}


//magnitude function

int magnitudeFct(){
    for(int i=0; i<sizeof(x_array); i++){

        //calculating the magnitude and adding the outcome to an array
        float magnitude = sqrt(pow(x_array[i],2) + pow(y_array[i],2));
        magnitude_array.push_back(magnitude);
    }
    std::cout << "The values of the magnitudes have been added to the vector." << std::endl; //check-point
    return 0;
}


// calculating the straight line function

int straightLine(){
    
    //define variables
    float chi, chi_square, gradient_value, intercept_value;  
    int N = x_array.size();

    //looping over all values
    for(int i=0; i<x_array.size(); i++){
        // calculating the component equal to the product of x and y
        float xy = x_array[i] * y_array[i];
        xy_array.push_back(xy);
        // calculating the component equal to x square
        float x2 = pow(x_array[i],2);
        x2_array.push_back(x2);}
        
    // summing over 
    float xy_sum = accumulate(xy_array.begin(),xy_array.end(),0.0f);
    float x2_sum = accumulate(x2_array.begin(),x2_array.end(),0.0f);
    float X = accumulate(x_array.begin(),x_array.end(),0.0f);
    float Y = accumulate(y_array.begin(),y_array.end(),0.0f);

    //gradient and intercept values
    gradient_value = ( N * xy_sum - X * Y ) / ( N * x2_sum - X * X );
    intercept_value = ( x2_sum * Y - xy_sum * X ) / ( N * x2_sum - X * X );
    
    //chi square test
    for(int i=0; i<x_array.size(); i++){
        chi = pow( (y_array[i] - (gradient_value*x_array[i] +intercept_value) ),2) / pow(error_y[i],2);
        chi_array.push_back(chi);}
    chi_square = accumulate(chi_array.begin(),chi_array.end(),0.0f); 

    //final equation and chi square - print and copy to new file
    std::string equation = std::to_string(gradient_value) + " * x + " + std::to_string(intercept_value);
    std::string goodness = "The value of chi square is " + std::to_string(chi_square);
    std::cout << "The fitting function has equation " << equation << std::endl;
    std::cout << goodness << std::endl;
    std::string fileName = "NewFile.txt";
    std::ofstream outputFile(fileName);
    outputFile << equation;
    outputFile << goodness;
    outputFile.close();

    return 0;
}


