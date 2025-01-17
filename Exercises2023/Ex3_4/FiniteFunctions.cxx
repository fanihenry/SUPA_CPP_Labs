#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way
#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//defining vectors outside the scope of the functions
std::vector<double> dataset;

//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);} //(overridable)

/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 

double FiniteFunction::integrate(int Ndiv){ //private
  //ToDo write an integrator
  //Integrating using Simpson's rule

  double a = -5.0;
  double b = 5.0;
  
  if (Ndiv % 2 != 0) {
      std::cerr << "Number of intervals must be even for Simpson's rule." << std::endl;
      return -99;}

  double h = (b - a) / Ndiv;
  double result = invxsquared(a) + invxsquared(b);

  for (int i = 1; i < Ndiv; i += 2) {
      result += 4 * invxsquared(a + i * h);}
  for (int i = 2; i < Ndiv - 1; i += 2) {
      result += 2 * invxsquared(a + i * h);}
  return h / 3.0 * result;  
}

double FiniteFunction::integral(int Ndiv) { //public
  std::cout << "Integral starting now" << std::endl;
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 100;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
// Derivation of the parameters for the distributions
###################
*/

// Mean
double FiniteFunction::x_mean(){
  double result = (accumulate(dataset.begin(),dataset.end(),0.0f))/dataset.size();
  return result;
}

// Standard deviation (o)
double FiniteFunction::standard_deviation(){
  std::vector<double> std_dev_array;
  double x_mean = this->x_mean();
  for(int i=0; i<sizeof(dataset); i++){
        double std_dev = pow(dataset[i]-x_mean,2);
        std_dev_array.push_back(std_dev);}
  double sum = accumulate(std_dev_array.begin(),std_dev_array.end(),0.0f);
  double result = std::sqrt(sum/sizeof(dataset));
  return result;
}

/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


//double FiniteFunction::operator()(double x) {
  //return 0.0*x ;}

/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}

/*
############################################################################
//New functions I have added
############################################################################
*/ 


/*
###################
//Normal Distribution class
###################
*/ 

//Normal distribution
double NormalDis::normal_fct(double x){
    
    double u=x_mean();
    double o=standard_deviation();
    
    double step1 = 1/(o*std::sqrt(2*M_PI));
    double step2 = pow((x-u)/o,2);
    double result = step1 * exp(-step2/2);
    return result;
}

double NormalDis::callFunction(double x){return this->normal_fct(x);} //(overridable)

//double NormalDis::operator()(double x){return this->normal_fct(x);} //(overridable)

double NormalDis::integrate(int Ndiv){ //private
  //ToDo write an integrator
  //Integrating using Simpson's rule

  double a = -5.0;
  double b = 5.0;
  
  if (Ndiv % 2 != 0) {
      std::cerr << "Number of intervals must be even for Simpson's rule." << std::endl;
      return -99;}

  double h = (b - a) / Ndiv;
  double result = normal_fct(a) + normal_fct(b);

  for (int i = 1; i < Ndiv; i += 2) {
      result += 4 * normal_fct(a + i * h);}
  for (int i = 2; i < Ndiv - 1; i += 2) {
      result += 2 * normal_fct(a + i * h);}
  return h / 3.0 * result; 
}


/*
###################
//Cauchy-Lorentz Class
###################
*/ 

//Cauchy-Lorentz distribution
double ChauchyLorentzDis::cauchy_lorentz_fct(double x){
    
    double gamma=1.4; //scalling factor, I evaluated the value with test and error
    double x0=-1; //position of the peak - I evaluated it graphically

    double step1 = pow((x-x0)/gamma,2);
    double result = 1 / (M_PI * gamma *(1+step1));
    return result;
}

double ChauchyLorentzDis::callFunction(double x){return this->cauchy_lorentz_fct(x);} //(overridable)

double ChauchyLorentzDis::integrate(int Ndiv){ //private
  //ToDo write an integrator
  //Integrating using Simpson's rule

  double a = -5.0;
  double b = 5.0;
  
  if (Ndiv % 2 != 0) {
      std::cerr << "Number of intervals must be even for Simpson's rule." << std::endl;
      return -99;}

  double h = (b - a) / Ndiv;
  double result = cauchy_lorentz_fct(a) + cauchy_lorentz_fct(b);

  for (int i = 1; i < Ndiv; i += 2) {
      result += 4 * cauchy_lorentz_fct(a + i * h);}
  for (int i = 2; i < Ndiv - 1; i += 2) {
      result += 2 * cauchy_lorentz_fct(a + i * h);}
  return h / 3.0 * result;  
}

/*
###################
//Crystal Ball Class
###################
*/ 

// Crystal Ball distribution
double CrystalBallDis::crystal_ball_fct(double x){
    
    //parameters
    double mean=x_mean();
    double o=standard_deviation();
    double n=2;
    double alpha=1;

    //derivations
    double A = pow(n/std::abs(alpha),n) * exp(-pow(std::abs(alpha),2)/2);
    double B = (n/std::abs(alpha)) - std::abs(alpha);
    double C = (n/std::abs(alpha))*(1/(n-1))*exp(-pow(abs(alpha),2)/2);
    double D = std::sqrt(M_PI/2)*(1+erf(std::abs(alpha)/std::sqrt(2)));
    double N = 1/(o*(C+D));
    double condition = (x-mean)/o;
    double result;

    if (condition>-alpha){
      result = N*exp(-pow(x-mean,2)/(2*pow(o,2)));}
    else if (condition<=-alpha){
      result = N*A*pow(B-(x-mean)/o,-n);}
    return result;
}

double CrystalBallDis::callFunction(double x){return this->crystal_ball_fct(x);} //(overridable)

double CrystalBallDis::integrate(int Ndiv){ //private
  //ToDo write an integrator
  //Integrating using Simpson's rule

  double a = -5.0;
  double b = 5.0;
  
  if (Ndiv % 2 != 0) {
      std::cerr << "Number of intervals must be even for Simpson's rule." << std::endl;
      return -99;}

  double h = (b - a) / Ndiv;
  double result = crystal_ball_fct(a) + crystal_ball_fct(b);

  for (int i = 1; i < Ndiv; i += 2) {
      result += 4 * crystal_ball_fct(a + i * h);}
  for (int i = 2; i < Ndiv - 1; i += 2) {
      result += 2 * crystal_ball_fct(a + i * h);}
  return h / 3.0 * result;  
}


/*
###################
//Reading function
###################
*/ 

std::vector<double> reading(std::string fileName){

    // open and read the file
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()){ std::cout << "File is open" << std::endl;}
    else{std::cout << "File is not open" << std::endl;}

    // loop over every line and store the values in a vector
    std::string line;  
    int lineNumber = 0;
    double x;

    while(std::getline(inputFile,line)){
        std::string x_string = line.substr(0, line.find(","));
        x = std::stof(x_string);
        dataset.push_back(x);
        lineNumber++;}

    //closing the file
    inputFile.close();
    std::cout << "File is closed" << std::endl; //check-point

    return dataset;
}

/*
###################
//Sampling functions
###################
*/ 

//generating random number x
double FiniteFunction::sampling_x(){
  std::random_device seed;
  std::mt19937 gen(seed());
  std::uniform_real_distribution<double> distribution(-10.0, 10.0);
  double x = distribution(gen);
  //std::cout << "x is " << x << std::endl; //check-point
  return x;
}

//generate random number y (different function for each class)
double NormalDis::sampling_y(double x){
  std::random_device seed2;
  std::mt19937 gen2(seed2());
  std::normal_distribution<double> distribution2(x, 3.0); //with mean=x and standard deviation=3 (arbitrarily chosen)
  double y = distribution2(gen2);
  //std::cout << "y is " << y << std::endl; //check-point
  return y;
}
double ChauchyLorentzDis::sampling_y(double x){
  std::random_device seed2;
  std::mt19937 gen2(seed2());
  std::cauchy_distribution<double> distribution2(x, 1.55);
  double y = distribution2(gen2);
  //std::cout << "y is " << y << std::endl; //check-point
  return y;
}
double CrystalBallDis::sampling_y(double x){
  std::random_device seed2;
  std::mt19937 gen2(seed2());
  std::normal_distribution<double> distribution2(x, 3.0); //THIS SHOULD BE A CRYSTAL BALL DISTRIBUTION AND NOT A NORMAL DISTRIBUTION
  double y = distribution2(gen2);
  //std::cout << "y is " << y << std::endl; //check-point
  return y;
}

//generating random number T between 0 and 1
double FiniteFunction::sampling_T(){
  std::random_device seed3;
  std::mt19937 gen3(seed3());
  std::uniform_real_distribution<double> distribution3(0.0, 1.0);
  double T = distribution3(gen3);
  //std::cout << "T is " << T << std::endl; //check-point
  return T;
}

//calculating A (different function for each class)
double NormalDis::sampling_A(double x, double y){
  double f_x = this->normal_fct(x);
  double f_y = this->normal_fct(y);
  double A = std::min(f_y / f_x, 1.0);
  //std::cout << "A is " << A << std::endl; //check-point
  return A;
}
double ChauchyLorentzDis::sampling_A(double x, double y){
  double f_x = this->cauchy_lorentz_fct(x);
  double f_y = this->cauchy_lorentz_fct(y);
  double A = std::min(f_y / f_x, 1.0);
  //std::cout << "A is " << A << std::endl; //check-point
  return A;
}
double CrystalBallDis::sampling_A(double x, double y){
  double f_x = this->crystal_ball_fct(x);
  double f_y = this->crystal_ball_fct(y);
  double A = std::min(f_y / f_x, 1.0);
  //std::cout << "A is " << A << std::endl; //Check-point
  return A;
}