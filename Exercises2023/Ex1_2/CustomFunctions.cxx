// Definitions of functions for AnalyseData.cxx

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CustomFunctions.h"

//defining vectors outside the scope of the functions
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
std::vector<float> x_power_array;
int amount=1;

//////////////////////////
/*

READING function

This function takes as the name of a file as argument, reads every every line and write the value of 
x and y into separate vectors. 

*/
//////////////////////////

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

////////////////////// 
/*

READING function - for errors

This function also reads a file and puts the error values of the x and y coordinate into separate vectors. 
Ideally, only one reading function should be used, but I spent a lot of time trying to combine them
and kept having issues with the scope of vectors.

*/ 
//////////////////////

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

//////////////////////
/* 

PRINTING function

This function should be used after a reading dunction. It reads the vectors containing the x and y 
coordinates, calculates the magnitude of the vector from the origin to that data point, and 
prints to the terminal the magnitude for the number of data points given as argument. 

*/
//////////////////////

int printing(int lineNumber) {
    double x;
    double y;

    //return error message if the number of line is too high, and taking the max number of lines
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

////////////////////
/*

MAGNITUDE function

This function calculates the magnitude of the vector from the origin to the data point and 
adds this value to a vector. 

*/
////////////////////

std::vector<float> magnitudeFct(){
    
    //calculating the magnitude and adding the outcome to an array
    for(int i=0; i<sizeof(x_array); i++){
        float magnitude = sqrt(pow(x_array[i],2) + pow(y_array[i],2));
        magnitude_array.push_back(magnitude);}

    std::cout << "The values of the magnitudes have been added to the vector." << std::endl; //check-point
    return magnitude_array;
}

////////////////////////
/*

STRAIGHT LINE function

This function derives the equation of the straight line that fits the data the best. It uses the
least squares method to determine the value of the gradient and intercept of the best fit. It also
calculates the value of the chi square in order to evaluate the goodness of the fit. This function
returns a string which contains the equation of the best fit and the value of chi square. 

*/
////////////////////////

std::string straightLine(){
    
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

    // print and save the output into a string
    std::string equation = "The fitting function has equation " + std::to_string(gradient_value) + " * x + " + std::to_string(intercept_value);
    std::string goodness = "The value of chi square is " + std::to_string(chi_square);
    std::cout << equation << std::endl;
    std::cout << goodness << std::endl;
    std::string lineString = equation + "\n" + goodness;

    return lineString;
}

/////////////////////
/*

POWER function

This function calculates the value of x^y. It is an alternative to the pow() function and does not 
use any loop. !! Be careful: this function is recursive. !!

*/
/////////////////////

float power(float x, float y, float r) {

    //rounding y to the above integer
    int y_int = (int)y+1;
    float result;
    
    //repeating the function for y times 
    if (amount==y_int){
        return r;}
    else if (amount<y_int){
        amount++ ;}
    else {
        std::cout << "Error??" << std::endl;
        return 1;}
    return power(x,y,x*r);
}

//////////////////////
/*

POWER function - for the whole dataset

This function uses the above general power function, but applies it to the whole dataset and 
adds the values to another vector.

*/
//////////////////////

std::vector<float> power_dataset(){

    //looping over all values in the dataset
    for(int i=0; i<x_array.size(); i++){
        float x_power;

        //resetting iterations
        amount=1;

        // calculating x^y
        x_power = power(x_array[i],y_array[i],x_array[i]);
        x_power_array.push_back(x_power);}

    return x_power_array;
}

////////////////////////
/*

OUTPUT FILE function 

This function adds the output of another function into a new file. It takes a string as argument and 
can be used for 3 different functions (power_dataset(), magnitudeFct() and straightLine()). In order
to use this function with a different function, another if statement needs to be added. 

*/
////////////////////////

int output_file(std::string fct){

    //power function
    if (fct=="power_dataset"){
        
        std::string fileName = "FilePower.txt";
        std::ofstream outputFile(fileName);
        outputFile << "For each data point, the value of x^y is" << '\n';
        std::vector<float> result = power_dataset();

        for (int i=0; i<result.size(); i++){
            float element = result[i];
            outputFile << element << '\n';}

        outputFile.close();
        std::cout << "The output has been added to the following file: " << fileName << std::endl;
    }

    //magnitude function
    else if (fct=="magnitude"){

        std::string fileName = "FileMagnitude.txt";
        std::ofstream outputFile(fileName);
        outputFile << "For each data point, the magnitude of the vector is:" << '\n';
        std::vector<float> result = magnitudeFct();

        for (int i=0; i<result.size(); i++){
            float element = result[i];
            outputFile << element << '\n';}

        outputFile.close();
        std::cout << "The output has been added to the following file: " << fileName << std::endl;}
    
    //straight line function
    else if (fct=="line"){

        std::string fileName = "FileLine.txt";
        std::ofstream outputFile(fileName);
        std::string result = straightLine();
        outputFile << result;
        outputFile.close();
        std::cout << "The output has been added to the following file: " << fileName << std::endl;}

    return 0;
}