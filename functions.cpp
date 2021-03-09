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
  
  //checks if the content is a valid double ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

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

  //checks if the content is a valid int ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

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
  getline(cin,fname); //take user input filename
  string ts; //string being read in file
  double tempv; //temp storage for valid doubles
  int tempi; //temp storage for valid start index

  fstream fin;
  fin.open(fname);
  if(!fin) //if file not found/invalid, throw error
  {
    cout<<"Error, file not detected. Try again.\n\n";
    return 0;
  }
  else //check for possible index on first line
  {
    fin >> ts; //check first string in file

    //if not int, either no specified index or invalid file
    if(!isInt(ts,tempi))
    {
      cout << "Index not specified, checking if valid double.\n";
      
      //if first entry is not double, invalid file
      if(!isDouble(ts,tempv))
      {
        cout<<"Error, not a valid signal file.\n\n";
        return 0;
      }
      else //if double, set index to 0
      {
        cout<<"Valid signal file with start index 0 found.\n\n";
        start = 0;

        //returns to start of file so it may read signal value
        fin.seekg(0, fin.beg);
      }
    }
    else //if first entry is int
    {
      getline(fin,ts); //read the rest of the first line
  
      stringstream ss(ts);
      string ts2;
      ss >> ts2; //read string after the first int

      //if followed by double, first int is index
      if((isDouble(ts2,tempv)) && (!ts2.empty()))
      {
        cout<<"Valid signal file found.\n\n";
        start = tempi;
        fin.seekg(0, fin.beg);
        fin >> ts; //go to second string
      }
      else //if no double after, first int is signal value
      {
        cout<<"Valid signal file with start index 0 found.\n\n";
        fin.seekg(0, fin.beg);
        start = 0;
      }
    }

    while(!fin.eof()) //reads until end of file
    {
      fin >> ts; //reads the first string in a line

      //if double and not blank
      if((isDouble(ts,tempv)) && (ts != ""))
      {
        datain.push_back(tempv); //add value to data vector
      }
      else
      {
        break; //ends when start of line is not valid signal value
      }
      
      getline(fin,ts); //skips the rest of the line
    }
  }
  return 1;
}

//takes the end index of a signal
int getEnd(int start, int length)
{
  return start + length - 1;
}

//subtracts the average of all signal values from each index
void removeAve(vector<double> &data)
{
  double ave = 0;
  for(int i = 0; i < data.size(); i++)
  {
    ave = ave + data[i];
  }

  ave = ave / data.size(); //gets the average of signal values
  for(int j = 0; j < data.size(); j++)
  {
    data[j] = data[j] - ave; //subtracts average from signal values
  }
}

void shiftx(int duration, vector<double> &new_x, 
  vector<double> &xdata, vector<double> &ydata)
{
  //adds zeroes before the vector to account for shifted y
  for(int i = 0; i < ydata.size() - 1; i++)
  {
    new_x.push_back(0);
  }
  //outputs the original x vector
  for(int j = 0; j < xdata.size(); j++)
  {
    new_x.push_back(xdata[j]);
  }
  //adds the same number of zeroes after the vector 
  for(int k = 0; k < ydata.size() - 1; k++)
  {
    new_x.push_back(0);
  }
}

void shifty(int duration, vector<double> &new_y, vector<double> ydata)
{
  //outputs the original y vector
  for(int i = 0; i < ydata.size(); i++)
  {
    new_y.push_back(ydata[i]);
  }
  //adds zeroes so that the sum of products for r_xy can be performed
  for(int j = ydata.size(); j < duration; j++)
  {
    new_y.push_back(0);
  }
}

void get_r(int duration, vector<double> &r_xy, vector<double> &new_x,
  vector<double> &xdata, vector<double> &new_y, vector<double> &ydata)
{
  double r_xy_current = 0; //sum of products value for current index
  int currentIndex = 0; //current index of values being multiplied

   for(int i = 0; i < duration; i++) //loops for each lag value
  {
    r_xy_current = 0; //sets current value to 0 at the start
    currentIndex = ydata.size() - 1; //first index with an x value
    
    //sum of products for the range of indices containing x values
    for(int j = 0; j < xdata.size(); j++)
    {
      //sum of products for current index
      r_xy_current = r_xy_current + 
        (new_x[currentIndex] * new_y[currentIndex]);
      
      currentIndex++;
    }
    
    r_xy.push_back(r_xy_current); //add value to vector
    new_y.insert(new_y.begin(), 0); //shift y vector to the right by 1
  }  
}

void get_rho(int duration, vector<double> &xdata, 
vector<double> &ydata, vector<double> &r_xy, vector<double> &rho_xy)
{
  double r_xx = 0, r_yy = 0, normalize = 0;
  
  //autocorrelation of x
  for(int i = 0; i < xdata.size(); i++)
  {
    r_xx = r_xx + (xdata[i]*xdata[i]);
  }
  
  //autocorrelation of y
  for(int i = 0; i < ydata.size(); i++)
  {
    r_yy = r_yy + (ydata[i]*ydata[i]);
  }
  
  //normalization coefficient
  normalize = sqrt(r_xx*r_yy);
  
  //divide each value of r_xy by normalization coefficient
  for(int i = 0; i < duration; i++)
  {
    rho_xy.push_back(r_xy[i] / normalize);
  }
}

//for showing necessary data
void showdata(vector<double> data, string ttype)
{
  cout << ttype << ": ";
  for(int i = 0; i < data.size(); i++)
  {
    if(i == data.size() - 1)
    {
      cout << data[i];
    }
    else
    {
      cout << data[i] << ", ";
    }
  }
  cout << endl;
}

//for exporting to output file
void exportrho(int lag, vector<double> &rho_xy)
{
  ofstream output;
  string fname;
  cout<<"enter output file name: ";
  cin>>fname;

  output.open(fname);
  output << lag <<" "<< rho_xy[0]<<endl; //write start index

  for(int i = 1; i < rho_xy.size(); i++)
  {
    output << rho_xy[i] << endl; //write one value per line
  }
  output.close();
}
