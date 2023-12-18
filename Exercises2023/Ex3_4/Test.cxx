// Fani Henry - 06/12/2023
// Test code for SUPA C++ course 

/*

Next step: Sampling. 
Also, print some info about the distributions to the terminal.

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
    dataset = reading("Outputs/data/MysteryData21122.txt");
    std::cout << "check that reading fct is working: print line 5: " << dataset[4] << std::endl;
    
    //using a SWITCH to know which distribution to plot
    int binNumber = 1000;
    bool go=true;
    while(go){
        int i;
        std::cout << "Please enter a integer between 1 and 4." << std::endl;
        std::cout << "  1 = Plotting the default function." << std::endl;
        std::cout << "  2 = Plotting teh Normal distribution." << std::endl;
        std::cout << "  3 = Plotting the Cauchy-Lorentz distribution." << std::endl;
        std::cout << "  4 = Plotting the Crystall Ball distribution." << std::endl;
        std::cout << "0 = Exiting loop." << std::endl;
        std::cin >> i;
        
        switch (i){
            
            // Default function - plotting
            case 1:{
                FiniteFunction fct1;
                fct1.plotData(dataset,binNumber,true);
                fct1.plotFunction();
                break;}

            // Normal distribution - plotting
            case 2:{
                std::cout << "Plotting the Normal distribution" << std::endl;
                NormalDis fct2;
                double m_Integral=NULL;
                double M=fct2.x_mean();
                double SD=fct2.standard_deviation();
                std::cout << "the mean is " << M << std::endl;
                std::cout << "the standard deviation is " << SD << std::endl;
                fct2.plotData(dataset,binNumber,true);
                fct2.plotFunction();
                break;}

            // Cauchy-Lorentz distribution - plotting
            case 3:{
                std::cout << "Plotting the Cauchy-Lorentz distribution" << std::endl;
                ChauchyLorentzDis fct3;
                double m_Integral=NULL;
                double M=fct3.x_mean();
                double SD=fct3.standard_deviation();
                std::cout << "the mean is " << M << std::endl;
                std::cout << "the standard deviation is " << SD << std::endl;
                fct3.plotData(dataset,binNumber,true);
                fct3.plotFunction();
                break;}

            // Crystal Ball distribution - plotting
            case 4:{
                std::cout << "Plotting the Crytal Ball distribution" << std::endl;
                CrystalBallDis fct4;
                double m_Integral=NULL;
                double M=fct4.x_mean();
                double SD=fct4.standard_deviation();
                std::cout << "the mean is " << M << std::endl;
                std::cout << "the standard deviation is " << SD << std::endl;
                fct4.plotData(dataset,binNumber,true);
                fct4.plotFunction();
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
                break;}}}

    //sampling
    sampling();
    
    return 0;
}
