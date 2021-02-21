#include <iostream>
#include <sstream>
using namespace std;

bool isDouble(string s, double& value){
  double temp; //sets a temp variable
  bool check=(istringstream(s) >> temp >> ws).eof();
  //^checks if the content is all numeric ignoring whitespaces
  if(check==0){
    return false;
    //returns 0 without updating value
  }
  else{
    value = temp;
    return true;
    //returns 1 and updating value
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