#include <iostream>
#include <sstream>
using namespace std;

bool isDouble(string s, double& value){
  //long double ld;
  //cout<<(std::istringstream(s) >> value >> std::ws).eof();
  double temp;
  bool check=(istringstream(s) >> temp >> ws).eof();
  if(check==0){
    return false;
  }
  else{
    value = temp;
    return true;
  }

}

int main(){
  string in;
  double value=0;
  cout<<"enter string: ";
  cin>>in;

  cout<<"is "<<in<<" a double? \n0=no, 1=yes"<<endl;
  cout<<isDouble(in,value)<<endl;
  if(isDouble(in,value)==1){
    cout<<"float value: "<<value<<endl;
  }
  else{
    cout<<in<<" is not a double"<<endl;
  }


}