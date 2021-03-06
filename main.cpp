#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "functions.h"
#include "functions.cpp"
using namespace std;

int main(){
  cout<<"hello world"<<endl;
  cout<<"test v2"<<endl;
  cout<<"pog";
  //cout<<"hello world"<<endl;
  //cout<<"test maincpp";
  vector<double> xdata;
  vector<double> ydata;
  datain(xdata);

int main()
{
  vector<double> xdata, ydata;
  double xstart, ystart;
  char dtype='x';
  double temp;
 
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


  //test code -- move to dedicated functions later ---------------------------------------------------------------------------

  int lag = xstart - yend;

  int duration = xdata.size() + ydata.size() - 1;
  vector<double> new_x, new_y;

  //shifted y data
  for(int i = 0; i < ydata.size(); i++)
  {
    new_y.push_back(ydata[i]);
  }
  for(int j = ydata.size(); j < duration; j++)
  {
    new_y.push_back(0);
  }

  //shifted x data
  for(int i = 0; i < ydata.size() - 1; i++)
  {
    new_x.push_back(0);
  }
  for(int j = 0; j < xdata.size(); j++)
  {
    new_x.push_back(xdata[j]);
  }
  for(int i = 0; i < ydata.size() - 1; i++)
  {
    new_x.push_back(0);
  }

  //cout check ---

  cout << "new x = ";
  for(int i = 0; i < new_x.size(); i++)
  {
    cout << new_x[i] << ",";
  }
  cout << endl;
  
  cout << "new y = ";
  for(int i = 0; i < new_y.size(); i++)
  {
    cout << new_y[i] << ",";
  }

  cout << endl;

  //another function for r_xy ----------------------------------------------------------------

  double r_xy_current = 0;
  int currentIndex = 0;

  double r_xy [duration] = {};

  for(int i = 0; i < duration; i++)
  {
    r_xy_current = 0;
    currentIndex = ydata.size() - 1;
    
    for(int j = 0; j < xdata.size(); j++)
    {
      r_xy_current = r_xy_current + (new_x[currentIndex] * new_y[currentIndex]);
      currentIndex++;
    }
    
    r_xy[i] = r_xy_current;
    new_y.insert(new_y.begin(), 0);
  }

  //return r_xy in actual function maybe

  //cout check ---
  cout << "r_xy = ";
  for(int i = 0; i < duration; i++)
  {
    cout << r_xy[i] << ",";
  }
  cout << endl;

  //new function for finding rho_xy -------------------------------------------------------
  double rho_xy[duration] = {};

  //normalization coefficient
  double r_xx = 0, r_yy = 0, normalize = 0;

  for(int i = 0; i < xdata.size(); i++)
  {
    r_xx = r_xx + (xdata[i]*xdata[i]);
  }

  for(int i = 0; i < ydata.size(); i++)
  {
    r_yy = r_yy + (ydata[i]*ydata[i]);
  }

  normalize = sqrt(r_xx*r_yy);

  for(int i = 0; i < duration; i++)
  {
    rho_xy[i] = r_xy[i] / normalize;
  }

  //cout check ---
  cout << "rho_xy = ";
  for(int i = 0; i < duration; i++)
  {
    cout << rho_xy[i] << ",";
  }
  cout << endl;
}