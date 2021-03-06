#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "functions.h"
#include "functions.cpp"
using namespace std;

int main()
{
  vector<double> xdata, ydata;
  double xstart, ystart;
  char dtype='x';
  double temp;
  string ttype;
 
  while(!datain(xdata, dtype, xstart))
  { //empty since its just an entry check
  }

  dtype='y';
  while(!datain(ydata,dtype,ystart))
  {//empty since its just an entry check
  }

//for testing if it got the whole dataset in, can comment out later
  for(int i=0;i<xdata.size();i-=-1)
  {
    cout<<"start index: "<<xstart<<endl;
    cout<<xdata[i]<<endl;
  }
  for(int i=0;i<ydata.size();i-=-1)
  {
    cout<<"start index: "<<ystart<<endl;
    cout<<ydata[i]<<endl;
  }

  int xend = getEnd(xstart, xdata.size());
  int yend = getEnd(ystart, ydata.size());

  cout << endl << xend << endl << yend << endl;

  int xend = getEnd(xstart, xdata.size());
  int yend = getEnd(ystart, ydata.size());

  cout << endl << xend << endl << yend << endl;

  removeAve(xdata);
  removeAve(ydata);


  //test code -- move to dedicated functions later
  int lag = xstart - yend;

  int duration = xdata.size() + ydata.size() - 1;
  vector<double> new_x, new_y;

  shiftx(duration, new_x, xdata, ydata);
  shifty(duration, new_y, ydata);


  //cout check ---
  ttype = "new x";
  showdata(new_x,ttype);
  ttype = "new y";
  showdata(new_y,ttype);
  
  //another function for r_xy 
  vector<double> r_xy;
  get_r(duration, r_xy, new_x, xdata, new_y, ydata);


  //cout check ---
  ttype = "r_xy";
  showdata(r_xy,ttype);
  
  //new function for finding rho_xy 
  vector<double> rho_xy;
  get_rho(duration, xdata, ydata, r_xy, rho_xy);
  
  //cout check ---
  ttype = "rho_xy";
  showdata(rho_xy,ttype);
}