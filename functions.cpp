#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "functions.h"
using namespace std;

bool isDouble(string s, double& value)
{
  double temp; //sets a temp variable
  bool check = (istringstream(s) >> temp >> ws).eof();
  //^checks if the content is all numeric ignoring whitespaces

  if(check == 0)
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

bool isInt(string s, int& value)
{
  int temp; //sets a temp variable
  bool check = (istringstream(s) >> temp >> ws).eof();
  //^checks if the content is all numeric ignoring whitespaces

  if(check == 0)
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


bool datain(vector<double> &datain, char dtype, int &start)
{
  
  string fname;
  cout << "File Name for " << dtype << ": ";
  getline(cin,fname);
  string ts;
  double tempv;
  int tempi;

  fstream fin;
  fin.open(fname);
  if(!fin)
  {
    cout<<"error, file not detected. try again.\n";
    return 0;
  }
  else
  {
    fin >> ts;
    if(!isInt(ts,tempi))
    {
      cout << "not valid index, checking if valid double\n";
      if(!isDouble(ts,tempv))
      {
        cout<<"error, not a valid signal file.\n";
        return 0;
      }
      else
      {
        cout<<"Valid signal file with start index 0 found\n";
        start = 0;
        fin.seekg(0, fin.beg);
      }
    }
    else
    {
      cout<<"Valid signal file found.\n";
      start = tempi;
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

int getEnd(int start, int length)
{
  return start + length - 1;
}

void removeAve(vector<double> &data)
{
  double ave = 0;
  for(int i = 0; i < data.size(); i++)
  {
    ave = ave + data[i];
  }

  ave = ave / data.size();
  //cout << endl << "ave = " << ave << endl;
  for(int j = 0; j < data.size(); j++)
  {
    data[j] = data[j] - ave;
    //cout << data[j] << ",";
  }
}

void shiftx(int duration, vector<double> &new_x, 
            vector<double> &xdata, vector<double> &ydata)
{
  for(int i = 0; i < ydata.size() - 1; i++)
  {
    new_x.push_back(0);
  }
  for(int j = 0; j < xdata.size(); j++)
  {
    new_x.push_back(xdata[j]);
  }
  for(int k = 0; k < ydata.size() - 1; k++)
  {
    new_x.push_back(0);
  }
}

void shifty(int duration, vector<double> &new_y, vector<double> ydata)
{
  for(int i = 0; i < ydata.size(); i++)
  {
    new_y.push_back(ydata[i]);
  }
  for(int j = ydata.size(); j < duration; j++)
  {
    new_y.push_back(0);
  }
}

void get_r(int duration, vector<double> &r_xy, vector<double> &new_x,
          vector<double> &xdata, vector<double> &new_y,
          vector<double> &ydata)
{
  double r_xy_current = 0;
  int currentIndex = 0;

   for(int i = 0; i < duration; i++)
  {
    r_xy_current = 0;
    currentIndex = ydata.size() - 1;
    
    for(int j = 0; j < xdata.size(); j++)
    {
      r_xy_current = r_xy_current + 
                    (new_x[currentIndex] * new_y[currentIndex]);
      currentIndex++;
    }
    
    r_xy.push_back(r_xy_current);
    new_y.insert(new_y.begin(), 0);
  }
  
}

void get_rho(int duration, vector<double> &xdata, 
vector<double> &ydata, vector<double> &r_xy, vector<double> &rho_xy)
  {
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
      rho_xy.push_back(r_xy[i] / normalize);
    }
  }

void showdata(vector<double> data, string ttype)
{
  cout << ttype << " = ";
  for(int i = 0; i < data.size(); i++)
  {
    cout << data[i] << ", ";
  }
  cout << endl;
}

void exportrho(int lag, vector<double> &rho_xy)
{
  ofstream output;
  string fname;
  cout<<"enter output file name: ";
  cin>>fname;

  output.open(fname);
  output << lag <<" "<< rho_xy[0]<<endl;

  for(int i = 1; i < rho_xy.size(); i-=-1)
  {
    output << rho_xy[i] << endl;
  }
  output.close();
}
