#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "functions.cpp"

using namespace std;

bool isDouble(string s, double& value);

bool isInt(string s, int& value);

bool datain(vector<double> &datain, char dtype, int &start);

int getEnd(int start, int length);

void removeAve(vector<double> &data);

void shiftx(int duration, vector<double> &new_x, 
  vector<double> &xdata, vector<double> &ydata);

void shifty(int duration, vector<double> &new_y, 
  vector<double> ydata);

void get_r(int duration, vector<double> &r_xy, vector<double> &new_x,
  vector<double> &xdata, vector<double> &new_y, 
  vector<double> &ydata);

void get_rho(int duration, vector<double> &xdata, 
  vector<double> &ydata, vector<double> &r_xy, 
  vector<double> &rho_xy);

void showdata(vector<double> data,string ttype);

void exportrho(int lag, vector<double> &rho_xy);

#endif