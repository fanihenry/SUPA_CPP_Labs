// Fani Henry - 06/12/2023
// Assignement 2 for SUPA C++ course 

/*

This script is for the second assignement of the SUPA C++ course 2023.
This script should be compile using the Makefile. The required functions are defined in the
FiniteFunctions.cxx and FiniteFunctions.h files. 

The first part of the script aims to determine which function some mystery data was sampled from. 
Three distributions are tested: a normal dictribution, a Cauchy-Lorentz distribution and a Crystal 
Ball distribution. The user can write in the terminal which function they whish to try. The script 
will then create a plot with the mystery data and the chosen distribution. 

In the second part of the script, some data is sampled from a chosen distribution. the script generates 
a plot that overlays the chosen distribution, the sampled data and the initial mystery data. The plots 
are saved as ./Outputs/pgn/DefaultFunction.png.

*/

#include <iostream>
#include <cmath>
#include "FiniteFunctions.h"

int main(){
    
    //FITTING

    //read the data and store it in a vector
    std::vector<double> dataset;
    dataset = reading("Outputs/data/MysteryData21122.txt");
    //std::cout << "check that reading fct is working: print line 5: " << dataset[4] << std::endl; //check-point
    
    //using a SWITCH to know which distribution to plot
    int binNumber = 1000;
    bool go=true;
    while(go){
        int i;
        std::cout << "FITTING - Which function to you want to plot on the mystery data? Please enter a integer between 1 and 4." << std::endl;
        std::cout << "  1 = Plotting the default function." << std::endl;
        std::cout << "  2 = Plotting the Normal distribution." << std::endl;
        std::cout << "  3 = Plotting the Cauchy-Lorentz distribution." << std::endl;
        std::cout << "  4 = Plotting the Crystall Ball distribution." << std::endl;
        std::cout << "  0 = Exiting loop." << std::endl;
        std::cin >> i;
        
        switch (i){
            
            // Default function - plotting
            case 1:{
                std::cout << "Plotting the default function..." << std::endl;
                FiniteFunction fct1;
                fct1.plotData(dataset,binNumber,true);
                fct1.plotFunction();
                fct1.printInfo();
                std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
                std::cout << "We can see that the data was NOT sampled from the default function." << std::endl;
                break;}

            // Normal distribution - plotting
            case 2:{
                std::cout << "Plotting the Normal distribution..." << std::endl;
                NormalDis fct2;
                double m_Integral=NULL;
                double M=fct2.x_mean();
                double SD=fct2.standard_deviation();
                fct2.printInfo();
                std::cout << "mean: " << M << std::endl;
                std::cout << "standard deviation: " << SD << std::endl;
                fct2.plotData(dataset,binNumber,true);
                fct2.plotFunction();
                std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
                std::cout << "We can see that the data was sampled from a normal distribution." << std::endl;
                break;}

            // Cauchy-Lorentz distribution - plotting
            case 3:{
                std::cout << "Plotting the Cauchy-Lorentz distribution..." << std::endl;
                ChauchyLorentzDis fct3;
                double m_Integral=NULL;
                double M=fct3.x_mean();
                double SD=fct3.standard_deviation();
                fct3.printInfo();
                std::cout << "mean: " << M << std::endl;
                std::cout << "standard deviation: " << SD << std::endl;
                fct3.plotData(dataset,binNumber,true);
                fct3.plotFunction();
                std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
                std::cout << "We can see that the data was NOT sampled from a Cauchy-Lorentz distribution." << std::endl;
                break;}

            // Crystal Ball distribution - plotting
            case 4:{
                std::cout << "Plotting the Crytal Ball distribution..." << std::endl;
                CrystalBallDis fct4;
                double m_Integral=NULL;
                double M=fct4.x_mean();
                double SD=fct4.standard_deviation();
                fct4.printInfo();
                std::cout << "mean: " << M << std::endl;
                std::cout << "standard deviation: " << SD << std::endl;
                fct4.plotData(dataset,binNumber,true);
                fct4.plotFunction();
                std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
                std::cout << "We can see that the data was NOT sampled from a Crystall Ball distribution." << std::endl;
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

    //SAMPLING

    int distribution_choice;
    std::cout << "SAMPLING - Which distribution do you want to sample from? Please enter a integer between 1 and 3." << std::endl;
    std::cout << "  1 = Plotting teh Normal distribution." << std::endl;
    std::cout << "  2 = Plotting the Cauchy-Lorentz distribution." << std::endl;
    std::cout << "  3 = Plotting the Crystall Ball distribution." << std::endl;
    std::cout << "  0 = Exiting loop." << std::endl;
    std::cin >> distribution_choice;

    binNumber = 25;

    //NORMAL distribution
    if (distribution_choice==1){
        std::cout << "Sampling data from a Normal distribution..." << std::endl;
        NormalDis myFunction;
        std::vector<double> y_array;
        int i=0;
        double x=myFunction.sampling_x(); //generating the first random number x

        for (i=0; i<10000; i++){
            double y=myFunction.sampling_y(x);
            double A=myFunction.sampling_A(x,y);
            double T=myFunction.sampling_T();

            //accetance
            if (T<A){
                y_array.push_back(y);
                //std::cout << "T<A so we keep y." << std::endl; //check-point
                x=y;}
            else {
                //std::cout << "T>A so we don't keep y." << std::endl; //check-point
            }
        }

        //plotting
        std::cout << "Plotting the Normal distribution..." << std::endl;
        double m_Integral=NULL;
        double M=myFunction.x_mean();
        double SD=myFunction.standard_deviation();
        //std::cout << "the mean is " << M << std::endl; //check-point
        //std::cout << "the standard deviation is " << SD << std::endl; //check-point
        myFunction.plotData(y_array,binNumber,false);
        myFunction.plotData(dataset,100,true);
        myFunction.plotFunction();
        std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
    }


    // CAUCHY-LORENTZ distribution
    if (distribution_choice==2){
        std::cout << "Sampling data from a Cauchy-Lorentz distribution..." << std::endl;
        ChauchyLorentzDis myFunction2;
        std::vector<double> cauchy_sampling;
        int i=0;
        double x=myFunction2.sampling_x(); //generating the first random number x

        for (i=0; i<10000; i++){
            double y=myFunction2.sampling_y(x);
            double A=myFunction2.sampling_A(x,y);
            double T=myFunction2.sampling_T();

            //accetance
            if (T<A){
                cauchy_sampling.push_back(y);
                //std::cout << "T<A so we keep y." << std::endl; //check-point
                x=y;}
            else {
                //std::cout << "T>A so we don't keep y." << std::endl; //check-point
            }
        }

        //plotting
        std::cout << "Plotting the Cauchy-Lorentz distribution..." << std::endl;
        double m_Integral=NULL;
        double M=myFunction2.x_mean();
        double SD=myFunction2.standard_deviation();
        //std::cout << "the mean is " << M << std::endl; //check-point
        //std::cout << "the standard deviation is " << SD << std::endl; //check-point
        myFunction2.plotData(cauchy_sampling,binNumber,false);
        myFunction2.plotData(dataset,100,true);
        myFunction2.plotFunction();
        std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
    }

     // CRYSTAL BALL distribution
    if (distribution_choice==3){
        std::cout << "Sampling data from a Crystal Ball distribution..." << std::endl;
        CrystalBallDis myFunction2;
        std::vector<double> crystal_sampling;
        int i=0;
        double x=myFunction2.sampling_x(); //generating the first random number x

        for (i=0; i<10000; i++){
            double y=myFunction2.sampling_y(x);
            double A=myFunction2.sampling_A(x,y);
            double T=myFunction2.sampling_T();

            //accetance
            if (T<A){
                crystal_sampling.push_back(y);
                //std::cout << "T<A so we keep y." << std::endl; //check-point
                x=y;}
            else {
                //std::cout << "T>A so we don't keep y." << std::endl; //check-point
            }
        }

        //plotting
        std::cout << "Plotting the Crystal Ball distribution..." << std::endl;
        double m_Integral=NULL;
        double M=myFunction2.x_mean();
        double SD=myFunction2.standard_deviation();
        //std::cout << "the mean is " << M << std::endl; //check-point
        //std::cout << "the standard deviation is " << SD << std::endl; //check-point
        myFunction2.plotData(crystal_sampling,binNumber,false);
        myFunction2.plotData(dataset,100,true);
        myFunction2.plotFunction();
        std::cout << "The plot has been saved as DefaultFunction.png." << std::endl;
        std::cout << "**Note: I coundn't find a Crystal Ball fct to generate a random number (y) from, so I used the normal fct.**" << std::endl;
    }

    return 0;
}
