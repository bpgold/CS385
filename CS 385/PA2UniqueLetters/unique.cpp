/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Breona Pizzuta
 * Date        : 9/26/24
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (char letter : s){
        if (letter <'a' || letter > 'z') //letter is not between a-z
            return false; //false otherwise
    }
    return true; //all lower case letters 
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    unsigned int vector =0; //bit vector to track seen letters
    unsigned int setter; //setter
    for (char letter: s){
        int indexingBit= letter - 'a'; //current letters index 
        setter = 1 << indexingBit; //shift 1 by the indexingBit 

        //check if seen first
        if(vector & setter){
            return false;  //seen before, end 
        }
        vector= vector|setter; //mark seen
    }
    return true; //all unique

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if(argc != 2){
        cout << "Usage: ./unique <string>" <<endl; //wrong number of args
        return 1;
    }
    string message= argv[1]; //holds the string 

    if (!is_all_lowercase(message)) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (all_unique_letters(message)) {
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }

    return 0;

}
