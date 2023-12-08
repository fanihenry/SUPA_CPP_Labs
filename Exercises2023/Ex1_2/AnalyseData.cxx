// Fani Henry
// 15 Nov 2023
// SUPA C++ course - Lab 1

/* 

This is the first assignement of the SUPA C++ course, taken in 2023. 
This steering file needs to be ran with the CustomFunction.cxx and CustomFunction.h external 
files, which contain the necessary functions. This script interacts with the user via the terminal
and uses two data sets (input2D_float.txt and error2D_float.txt) to execute 3 tasks (calculating 
the magnitude of a vector, derivating the equation of a best fit line and calculating the value of x^y).

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "CustomFunctions.h"

int main(){
    
    //reading the data
    std::string fileName = "input2D_float.txt";
    reading(fileName);

    int i;
    bool go=true;

    //using a SWITCH to know which function to execute
    while(go){
        std::cout << "Please enter a integer between 1 and 3." << std::endl;
        std::cout << "1 = Calculating the magnitude of the vector to the point." << std::endl;
        std::cout << "2 = Fitting a straight line to the data and calculating chi square." << std::endl;
        std::cout << "3 = Computing the value of x^y." << std::endl;
        std::cout << "0 = Exiting loop." << std::endl;
        std::cin >> i;
        
        switch (i){

            //execute the magnitude function
            case 1:{
                std::cout << "You have chosen option 1 (Calculating the magnitude of the vector to the point)." << std::endl;
                
                //use the terminal input to define whether to print or calculate the magnitude
                std::string answer;
                std::cout << "Would you like to use the printing or calculating function? Answer with 'P' or 'C'." << std::endl;
                std::cin >> answer;
                
                //printing option
                if (answer=="P"){
                    int lineNumber;
                    std::string answer2;
                    std::cout << "How many lines would you like to print?" << std::endl;
                    std::cin >> answer2;
                    lineNumber = std::stoi(answer2);
                    printing(lineNumber);}

                //computing without printing option
                else if (answer=="C"){} //magnitudeFct();}
                else {std::cout << "Please type your answer in the format P or C.";}

                //writing the output to a new file
                output_file("magnitude");
                break;}
            
            //execute the straight line function
            case 2:{
                std::cout << "You have chosen option 2 (Fitting a straight line to the data and calculating chi square)." << std::endl;
                
                // reading the error files 
                std::string fileName2 = "error2D_float.txt";
                reading_error(fileName2);

                // computing the equation and writing the output to a new file
                output_file("line");
                break;}

            //execute the power function
            case 3:{
                std::cout << "You have chosen option 3 (Computing the value of x^y)." << std::endl;
                std::cout << "The values of x^y have been calculated for all the datapoints." << std::endl;
                
                // writing the output to a new file
                output_file("power_dataset");
                break;}

            // breaking the loop
            case 0:{
                std::cout << "You have chosen option 0 (Exit loop)." << std::endl;
                go=false;
                break;}
            default:{
                std::cout << "You didn't choose a valid option." << std::endl;
                std::cout << "Exit loop." << std::endl;
                go=false;
                break;}
        }    
    }
    return 0;
}
