#include <iostream>
#include <vector>
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



  
  
}