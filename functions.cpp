#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "functions.h"
using namespace std;

bool datain(std::vector<double> inD, char dtype, int &start)
{
  string fname;
  cout<<"File Name:";
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
    fin >> start;
    while(!fin.eof())
    {
      fin>>ts;
      if(isDouble(ts,tempv))
      {
        inD.push_back(tempv);
      }
    }

  }

}

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