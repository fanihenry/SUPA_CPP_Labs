// Separate File containing the functions fro Analysedata.cxx

#pragma once

//functions prototypes
int reading(std::string fileName);
int reading_error(std::string fileName2);
int printing(int lineNumber);
std::vector<float> magnitudeFct();
std::string straightLine();
float power(float x, float y, float r);
std::vector<float> power_dataset();
int output_file(std::string);