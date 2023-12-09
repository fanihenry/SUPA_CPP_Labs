// Definitions of functions for AnalyseData.cxx

// next step: define the ERF function in D in the CrystalBall function
// also define the condition on N for CrystalBall function

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include "CustomFunctions.h"

//defining vectors outside the scope of the functions


//functions

double normal(std::vector<double> x, double u, double o){
    double step1 = 1/(o*std::sqrt(2*M_PI));
    double step2 = pow((x-u)/o,2);
    double result = step1 * exp(-1/2 * step2);
    return result;
}

double CauchyLorentz(std::vector<double> x, double gamma, double x0){
    double step1 = pow((x-x0)/gamma,2);
    double result = 1 / (M_PI * gamma *(1+step1));
    return result;
}

double CrystalBall(std::vector<double> x, double alpha, double n, double o){
    double A = pow(n/abs(alpha),n) * exp(-pow(abs(alpha),2)/2);
    double B = (n/abs(alpha)) - abs(alpha);
    double C = (n/abs(alpha))*(1/(n-1))*(exp(-pow(abs(alpha),2))/2);
    double D = std::sqrt(M_PI/2)*(1+erf(abs(alpha)/std::sqrt(2)));
    double N = 1/(o*(C+D));

    if (N==){

    }
    else if (N==){

    }
}