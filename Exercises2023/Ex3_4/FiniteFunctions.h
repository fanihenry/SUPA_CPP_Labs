#include <string>
#include <vector>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

//general functions prototypes
std::vector<double> reading(std::string fileName);

//FiniteFunction 
class FiniteFunction{

public:
  FiniteFunction(); //Empty constructor
  FiniteFunction(double range_min, double range_max, std::string outfile); //Variable constructor
  ~FiniteFunction(); //Destructor
  double rangeMin(); //Low end of the range the function is defined within
  double rangeMax(); //High end of the range the function is defined within
  double integral(int Ndiv = 1000); 
  std::vector< std::pair<double,double> > scanFunction(int Nscan = 1000); //Scan over function to plot it (slight hack needed to plot function in gnuplot)
  void setRangeMin(double RMin);
  void setRangeMax(double RMax);
  void setOutfile(std::string outfile);
  void plotFunction(); //Plot the function using scanFunction
  double x_mean();
  double standard_deviation();
  double sampling_x();
  double sampling_T();
  
  //Plot the supplied data points (either provided data or points sampled from function) as a histogram using NBins
  void plotData(std::vector<double> &points, int NBins, bool isdata=true); //NB! use isdata flag to pick between data and sampled distributions
  virtual void printInfo(); //Dump parameter info about the current function (Overridable)
  virtual double callFunction(double x); //Call the function with value x (Overridable)

  //Protected members can be accessed by child classes but not users
protected:
  double m_RMin;
  double m_RMax;
  int m_IntDiv = 0; //Number of division for performing integral
  std::string m_FunctionName;
  std::string m_OutData; //Output filename for data
  std::string m_OutPng; //Output filename for plot
  std::vector< std::pair<double,double> > m_data; //input data points to plot
  std::vector< std::pair<double,double> > m_samples; //Holder for randomly sampled data 
  std::vector< std::pair<double,double> > m_function_scan; //holder for data from scanFunction (slight hack needed to plot function in gnuplot)
  bool m_plotfunction = false; //Flag to determine whether to plot function
  bool m_plotdatapoints = false; //Flag to determine whether to plot input data
  bool m_plotsamplepoints = false; //Flag to determine whether to plot sampled data 
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
  
private:
  double m_Integral;
  double invxsquared(double x); //The default functional form
  virtual double integrate(int Ndiv);
};

// New classes containing other functions I have added

class NormalDis : public FiniteFunction {
  private:
  double normal_fct(double x); 
  double callFunction(double x);
  double integrate(int Ndiv);
  public:
  double sampling_A(double x, double y);
  double sampling_y(double x);
};

class ChauchyLorentzDis : public FiniteFunction {
  private:
  double cauchy_lorentz_fct(double x); 
  double callFunction(double x);
  double integrate(int Ndiv);
  public:
  double sampling_A(double x, double y);
  double sampling_y(double x);
};

class CrystalBallDis : public FiniteFunction {
  private:
  double crystal_ball_fct(double x); 
  double callFunction(double x);
  double integrate(int Ndiv);
  public:
  double sampling_A(double x, double y);
  double sampling_y(double x);
};
