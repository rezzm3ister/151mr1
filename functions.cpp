#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "functions.h"
using namespace std;


bool isDouble(string s, double& value)
{
  double temp; //sets a temp variable
  bool check=(istringstream(s) >> temp >> ws).eof();
  //^checks if the content is all numeric ignoring whitespaces

  if(check==0)
  {
    return false;
    //returns 0 without updating value
  }

  else
  {
    value = temp;
    return true;
    //returns 1 and updating value
  }

}

bool datain(vector<double> &datain, char dtype, double &start)
{
  
  string fname;
  cout<<"File Name for "<<dtype<<": ";
  getline(cin,fname);
  string ts;
  double tempv;

  fstream fin;
  fin.open(fname);
  if(!fin){
    cout<<"error, file not detected. try again.\n";
    return 0;
  }
  else
  {
    fin >> ts;
    if(!isDouble(ts,tempv))
    {
      cout<<"not valid file";
      return 0;
    }
    else
    {
      start = tempv;
    }
    while(!fin.eof())
    {
      fin>>ts;
      if(isDouble(ts,tempv))
      {
        datain.push_back(tempv);
      }
    }

  }
  return 1;
}


