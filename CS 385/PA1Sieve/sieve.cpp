/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Breona Pizzuta
 * Date        : 9/16/24
 * Description : Sieve of Eratosthenes
 * Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <cmath> //used for sqrt
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    //constructor 
    PrimesSieve(int limit);

    //destructor 
    //called automatically to delete
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    //this is the function to display the primes 
    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;  //pointer to the array, can use is_prime as if it is the arr itself 
    const int limit_; //search limit, n, enetered by user
    int num_primes_, max_prime_; //num_primes= how many; max= largest prime 

    // Method declarations
    void sieve(); //finds the primes up to the limit
    static int num_digits(int num);
};

//name of class :: constrcutor 
//just a different way to organize the code 
//creates the is_prime array
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl; //extra line to seperate the search 
    cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    //GIVEN CODE
    // width for displaying primes based digits in the largest prime
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1); // Calculate primes that fit in one row
    int current_row = 0; // To track primes in current row

    // All primes fit in one row
    if (num_primes_ <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i]) {
                if (current_row > 0) {
                    cout << " "; //one space between primes
                }
                cout << i;
                current_row++;
            }
        }
        cout << endl; //row end
    }
    // primes need multiple lines, format them with right-alignment
    else {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i]) {
                if (current_row > 0) {
                    cout << " "; //space between primes
                }
                cout << setw(max_prime_width) << i; //align based on the largest prime's digit count
                current_row++;

                if (current_row == primes_per_row) {
                    cout << endl;  //new row
                    current_row = 0; // Reset new row
                }
            }
        }
        // remaining primes were printed in the last row and not completed, end the row
        if (current_row > 0) {
            cout << endl;
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    //initalize 0s and 1s as false and everything else true
    //at the end we need to count num of primes and biggest 

    // First mark all numbers as prime initially (except 0 and 1)
    is_prime_[0] = is_prime_[1] = false; // 0 and 1 are not prime numbers
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true; // we can assume that all numbers >= 2 are prime for now
    }

    // sieve algorithm based on psedudocode 
    for (int i = 2; i <= sqrt(limit_); i++) { //only go up to the square root of the limit
        if (is_prime_[i]) { // If i is still marked as prime
            // Mark all multiples of i as not a prime
            for (int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false; // Multiples of i are not prime
            }
        }
    }

    // count and find largest primes 
    num_primes_ = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i]) {
            num_primes_++; // Increment the count of primes
            max_prime_ = i; // The last prime will be the largest
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    // Keep dividing the number by 10 until we reach 0 to count how many digits it has
    while (num != 0) {
        num /= 10; // Remove last digit
        digits++;  // Increment digit count
    }
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    // can use new or local var

    PrimesSieve sieve(limit); //instance
    sieve.display_primes(); //display
    return 0;
}
