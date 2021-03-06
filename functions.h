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

void shiftx(int duration, vector<double> &new_x, vector<double> &xdata,
            vector<double> &ydata);
void shifty(int duration, vector<double> &new_y, vector<double> ydata);

void get_r(int duration, vector<double> &r_xy, vector<double> &new_x,
          vector<double> &xdata, vector<double> &new_y, 
          vector<double> &ydata);
void get_rho(int duration, vector<double> &xdata, vector<double> &ydata, 
            vector<double> &r_xy, vector<double> &rho_xy);

void showdata(vector<double> data,string ttype);

#endif