#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <vector>

using namespace std;

bool datain(vector<double> &data, char dtype, int &start){
  string fname;
  cout<<"File Name:";
  getline(fname);

  fstream fin;
  fin.open(fname);
  if(!fin){
    cout<<"error, file not detected. try again.\n";
    return 0;
  }
  else
  {
    fin >> start;
    while(fin)
  }

}

bool isdouble()


#endif