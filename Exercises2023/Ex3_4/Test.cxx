// Fani Henry - 06/12/2023
// Test code for SUPA C++ course 

/*

Update: the data can be read and added to a vector called dataset

*/

#include <iostream>
#include <cmath>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

// test function 

int main(){
    
    //read the data and store it in a vector
    std::vector<double> dataset;
    int binNumber = 200;
    dataset = reading("Outputs/data/MysteryData21122.txt");
    std::cout << "check that reading fct is working: print line 5: " << dataset[4] << std::endl;

    //plotting the data
    FiniteFunction fct1;
    std::cout << "Main function is working." << std::endl;
    fct1.plotData(dataset,binNumber,true);
    fct1.plotFunction();

    return 0;
}
