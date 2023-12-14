// Fani Henry - 06/12/2023
// Test code for SUPA C++ course 

/*

Next step: I have added the definition of the mean and the standard deviation, but 
I now need to find where to define them so that their values is used in the Normal distribution. 
Once that's done, repeat for the next 2 distributions. 

(see finitefunctions.cxx line 287)

*/

#include <iostream>
#include <cmath>
#include "FiniteFunctions.h"

// test function 

int main(){
    
    //check-point
    std::cout << "Main function is working." << std::endl;
    
    //read the data and store it in a vector
    std::vector<double> dataset;
    int binNumber = 1000;
    dataset = reading("Outputs/data/MysteryData21122.txt");
    std::cout << "check that reading fct is working: print line 5: " << dataset[4] << std::endl;

    // Default function - plotting
    //FiniteFunction fct1;
    //fct1.plotData(dataset,binNumber,true);
    //fct1.plotFunction();

    // Normal distribution - plotting
    //std::cout << "Plotting the Normal distribution" << std::endl;
    //NormalDis fct2;
    //double m_Integral=NULL;
    //double M=fct2.x_mean();
    //double SD=fct2.standard_deviation();
    //std::cout << "the mean is " << M << std::endl;
    //std::cout << "the standard deviation is " << SD << std::endl;
    //fct2.plotData(dataset,binNumber,true);
    //fct2.plotFunction();

    // Cauchy-Lorentz distribution - plotting
    //std::cout << "Plotting the Cauchy-Lorentz distribution" << std::endl;
    //ChauchyLorentzDis fct3;
    //double m_Integral=NULL;
    //double M=fct3.x_mean();
    //double SD=fct3.standard_deviation();
    //std::cout << "the mean is " << M << std::endl;
    //std::cout << "the standard deviation is " << SD << std::endl;
    //fct3.plotData(dataset,binNumber,true);
    //fct3.plotFunction();

    // Crystal Ball distribution - plotting
    std::cout << "Plotting the Crytal Ball distribution" << std::endl;
    ChauchyLorentzDis fct4;
    double m_Integral=NULL;
    double M=fct4.x_mean();
    double SD=fct4.standard_deviation();
    std::cout << "the mean is " << M << std::endl;
    std::cout << "the standard deviation is " << SD << std::endl;
    fct4.plotData(dataset,binNumber,true);
    fct4.plotFunction();

    return 0;
}
