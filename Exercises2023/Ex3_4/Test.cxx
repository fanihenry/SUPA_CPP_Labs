// Fani Henry - 06/12/2023
// Test code for SUPA C++ course 

/*

Update: the data can be read and added to a vector called dataset

next step: define the vector that contains datapoint -> same way as for the first lab 

*/

#include <iostream>
#include <cmath>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

// test function 

int main(){
    
    std::vector<double> dataset;
    dataset = reading("Outputs/data/MysteryData21122.txt");
    std::cout << "check that reading fct is working: print line 5: " << dataset[4] << std::endl;

    //using the class FiniteFunction
    FiniteFunction fct1;
    std::cout << "Main function is working." << std::endl;
    fct1.plotData(dataset,10,true);

    return 0;
}
