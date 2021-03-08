#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"
using namespace std;

int main()
{
  vector<double> xdata, ydata; //vectors containing signal values
  int xstart, ystart; //starting indices for each signal
  char dtype = 'x';
  double temp;
 
  while(!datain(xdata, dtype, xstart))
  {
    //loops until valid file is provided
  }

  dtype = 'y';
  while(!datain(ydata,dtype,ystart))
  {
    //loops until valid file is provided
  }

  //shows starting indices and signal values of x and y
  cout<<"x start: "<<xstart<<endl;
  showdata(xdata,"x data");
  cout<<"y start: "<<ystart<<endl;
  showdata(ydata,"y data");

  //remove averages from each signal value
  removeAve(xdata);
  removeAve(ydata);

  //int xend = getEnd(xstart, xdata.size());

  int yend = getEnd(ystart, ydata.size());
  int lag = xstart - yend; //lag is the starting index for rho_xy
  int duration = xdata.size() + ydata.size() - 1;
  
  vector<double> new_x, new_y; //shifted vectors for calculations

  //shift vectors such that first value of x and last value of y are aligned 
  shiftx(duration, new_x, xdata, ydata);
  shifty(duration, new_y, ydata);

  showdata(new_x, "shifted x");
  showdata(new_y, "shifted y");
  
  //solving r_xy and rho_xy
  vector<double> r_xy;
  get_r(duration, r_xy, new_x, xdata, new_y, ydata);

  showdata(r_xy, "r_xy");
  
  vector<double> rho_xy;
  get_rho(duration, xdata, ydata, r_xy, rho_xy);
  
  showdata(rho_xy,"rho_xy");
  cout<<endl;

  //printing rho_xy as a valid signal file
  exportrho(lag, rho_xy);
}