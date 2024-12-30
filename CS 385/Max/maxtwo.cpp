/*******************************************************************************
* Filename: maxtwo.cpp
* Author : Breona Pizzuta
* Version : 1.0
* Date : 9/6/24
* Description: compute max of two command line arguments 
* Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
int n, m;

//int max(int n, int m){
  //  return (n>m)? n : m; //if n>m return n; otherwise m 
//}

int main(int argc, char* argv[]){

    istringstream iss; //iss is name of var

    //check the correct number of arguments 
    if(argc !=3){ //if they didnt type 3 args
        cerr << "Usage: " << argv[0] << "<int> <int>" << endl;
        //argv[0] a;lways holds the name of the program 
        return 1; //terminates 
    }

    //convert the chars into an actual integer
    iss.str(argv[1]); //put str into iss object
    if(!(iss >> n)){ //store int after conversion
        cerr<< "Error: first command line arg must be int" << endl;
        return 1;
    } 

    //must reset iss obj to make sure no garbage is left behind or use 2 sep iss
    iss.clear();

     //convert the chars into an actual integer
    iss.str(argv[2]); //put str into iss object
    if(!(iss >> m)){ //store int after conversion
        cerr<< "Error: second command line arg must be int" << endl;
        return 1;
    } 
    cout<< "n is: " << n<< endl;
    cout<< "m is: " << m<< endl;

    cout << "max(" << m << ", " << n << ") is: " << max(m, n) << endl;
    //max is provided by the package algorithms 






    return 0;
}