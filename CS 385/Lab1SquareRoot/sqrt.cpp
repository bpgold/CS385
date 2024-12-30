/*******************************************************************************
* Filename: sqrt.cpp
* Author : Breona Pizzuta
* Version : 1.0
* Date : 9/5/24
* Description: Compute the square root of a double using Newton's method.
* Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/

#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cmath> //abs 
using namespace std;

double sqrt(double num, double epsilon ) {
    //if a neg number 
    if (num<0){
        return numeric_limits<double>::quiet_NaN();
    }
    // if num= 0 or 1
    if(num==0 ){
        return num;
    }
    if(num==1 ){
        return num;
    }

    //otherwise we use newtons method 
    double lastGuess= num;
    double nextGuess= (lastGuess +num /lastGuess) /2 ;

    /*If the absolute value of the difference between lastGuess and nextGuess is less than or equal a very small 
    number, such as 0.0001, you can claim that nextGuess is the approximated
square root of n. Otherwise the value of nextGuess becomes the new value
of lastGuess and the approximation process is repeated. */ 

    while (abs(lastGuess - nextGuess) >= epsilon){
        lastGuess= nextGuess;
        nextGuess= (lastGuess +num /lastGuess) /2;
    }

    return nextGuess;
}




int main(int argc, char* argv[]){

    istringstream iss; //iss is name of var
    double num;
    double epsilon= 1e-7;


    //make sure 1 or 2 arguments have been given
    if(argc !=2 && argc !=3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1; //terminates here

    }

     //Convert the first argument 
    iss.str(argv[1]); //put str into iss object
    if(!(iss >> num)){ //store int after conversion
        cerr<< "Error: Value argument must be a double." << endl;
        return 1;
    } 

    //must reset iss obj to make sure no garbage is left behind or use 2 sep iss
    iss.clear();

    // Convert the second argument if it was given
    if (argc == 3) {
        iss.str(argv[2]);
        if (!(iss >> epsilon)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        // epsilon needs to be positive 
        if (epsilon <= 0) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }


    //computation
    double compute= sqrt(num, epsilon);

    //Fixed notation with 8 digits
    cout<< fixed << setprecision(8) <<compute << endl;

    return 0; 
    
}