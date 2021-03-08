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
  vector<double> xdata, ydata;
  int xstart, ystart;
  char dtype = 'x';
  double temp;
 
  while(!datain(xdata, dtype, xstart))
  { //empty since its just an entry check
  }

  dtype = 'y';
  while(!datain(ydata,dtype,ystart))
  {//empty since its just an entry check
  }

  cout<<"x start: "<<xstart<<endl;
  showdata(xdata,"x data: ");
  cout<<"y start: "<<ystart<<endl;
  showdata(ydata,"y data: ");

  int xend = getEnd(xstart, xdata.size());
  int yend = getEnd(ystart, ydata.size());

  cout << endl << xend << endl << yend << endl;

  removeAve(xdata);
  removeAve(ydata);

  int lag = xstart - yend;

  int duration = xdata.size() + ydata.size() - 1;
  
  vector<double> new_x, new_y;

  shiftx(duration, new_x, xdata, ydata);
  shifty(duration, new_y, ydata);

  showdata(new_x, "New X: ");
  showdata(new_y, "New Y: ");
  
  //solving r_xy and rho_xy
  vector<double> r_xy;
  get_r(duration, r_xy, new_x, xdata, new_y, ydata);

  showdata(r_xy, "R_xy");
  
  vector<double> rho_xy;
  get_rho(duration, xdata, ydata, r_xy, rho_xy);
  
  showdata(rho_xy,"Rho_xy: ");
  cout<<endl<<endl;

  //printing rho to txt
  exportrho(lag, rho_xy);
}