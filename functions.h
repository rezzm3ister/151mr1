#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "functions.h"

using namespace std;
bool isDouble(string s, double& value);

bool datain(vector<double> &data69, char dtype, int &start);
//bool datainv2(vector<double> &data);


int getEnd(int start, int length);
void removeAve(vector<double> &data);

#endif
#endif