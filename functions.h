#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>

using namespace std;

bool datain(vector<double> &datain, char dtype, double &start);

int getEnd(int start, int length);
void removeAve(vector<double> &data);

#endif
#endif