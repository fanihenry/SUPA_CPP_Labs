// Fani Henry
// 15 Nov 2023
// SUPA C++ course - Lab 1

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

//functions which are defined later
int reading();
int printing();


int main(){

    // open and read the file
    std::string fileName = "input2D_float.txt";
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // vectors containing the coordinates 
    std::vector<double> x_array;
    std::vector<double> y_array;

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

            //printing the (x,y) coordinates
            std::cout << "(" << x << "," << y << ")" << std::endl;

        }
        lineNumber++;
        
    }

    inputFile.close();

    return 0;
}

