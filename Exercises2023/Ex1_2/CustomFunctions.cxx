// Definitions of functions for AnalyseData.cxx

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

// defining vectors outside the scope of the functions
std::vector<double> x_array;
std::vector<double> y_array;
std::vector<double> magnitude_array;
std::vector<double> deviation_array;
std::vector<double> gradient_array;
std::vector<double> intercept_array;
std::vector<double> sum_array;

//reading function 

int reading(){

    // open and read the file
    std::string fileName = "input2D_float.txt";
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line 
    std::string line;  
    int lineNumber = 0;
    double x, y;

    while(std::getline(inputFile,line)){
        //std::cout << lineNumber << std::endl;
        if (lineNumber > 0) { //skipping the first line

            //std::cout << line << std::endl;
            
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
    inputFile.close();
    std::cout << "File is closed" << std::endl; //check-point
    return 0;
}

//printing function 

int printing(int lineNumber){
    double x;
    double y;

    if (lineNumber>x_array.size()){
        std::cout << "It exceeds the maximum number of lines, which is " << x_array.size() <<std::endl;
        lineNumber = x_array.size();
    }

    for(int i=0; i<lineNumber; i++){

        //getting the coordinates
        x = x_array[i];
        y = y_array[i];

        //calculating the magnitude and printing the outcome
        float magnitude = sqrt(pow(x,2) + pow(y,2));
        std::cout << "For the point " << i << " with coordinates (" << x << "," << y << ")"<< ", the magnitude of the vector is " << magnitude << std::endl;
        magnitude_array.push_back(magnitude);
    }
    //std::cout << "Printing function is working" << std::endl; //check-point
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

// calculating the straight lien function

int straightLine(){
    
    //define variables
    float gradient=3;
    float intercept=2;
    float deviation, sum;
    const int size=10;
    int gradient_array[size], intercept_array[size];

    std::iota(gradient_array, gradient_array+size, 1);
    std::iota(intercept_array, intercept_array+size, 1);

    // calculations using the least mean square method, looping over various values for the gradient and intercept
    for (int g=0; g<size; g++){
        gradient = gradient_array[g];

        for (int n=0; n<size; n++){
            intercept = intercept_array[n];

            for(int i=0; i<x_array.size(); i++){
                deviation = pow( ((gradient * x_array[i] + intercept) - y_array[i]) ,2) ;
                deviation_array.push_back(deviation);
                std::cout << deviation << std::endl;
            }

            sum = accumulate(deviation_array.begin(),deviation_array.end(),0.0f);
            //std::cout << "The sum is " << sum << std::endl;
            sum_array.push_back(sum);
            std::cout << "The sum value " << sum << " for gradient " << g << " and intercept " << n << " has been added to the list" << std::endl;
        }
    }
    return 0;
}