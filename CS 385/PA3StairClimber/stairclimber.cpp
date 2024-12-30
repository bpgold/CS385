/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Breona Pizzuta 
 * Date        : 10/2/24
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    //storage vector for combos of stairs
    vector<vector<int>> combo_ways;

    //we start with the base case; no stairs left to climb 
    if (num_stairs <= 0)
    {
        combo_ways.push_back(vector<int>());
    }
    else
    {
        // we want to loop through the steps (1, 2, or 3)
        for (int i = 1; i <= 3; i++)
        {
            // we can only continue if we can take the step
            if (num_stairs >= i)
            {
                // we want to get the ways to climb the remaining stairs recursively
                vector<vector<int>> ways = get_ways(num_stairs - i);
                
                // prepend the current step to each of the returned ways
                for (vector<int>& way : ways)
                {
                    way.insert(way.begin(), i);
                    combo_ways.push_back(way);  // Add the new way to the result
                }
            }
        }
    }
    return combo_ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

     // the number of ways to climb stairs
    int total_ways = ways.size();
    //  the width needed for numbering the output
    int label_width = to_string(total_ways).length();

    // show each way to climb the stairs
    for (size_t i = 0; i < ways.size(); i++)
    {
        cout << setw(label_width) << i + 1 << ". [";
        // Print each step in the current way
        for (size_t j = 0; j < ways[i].size(); j++)
        {
            cout << ways[i][j];
            if (j < ways[i].size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    // incorrect number of arguments
    if (argc != 2)
    {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    // take the number of stairs from the input argument
    istringstream iss(argv[1]);
    int stairs = 0;

    // invalid input; not a positive integer
    if (!(iss >> stairs) || stairs < 1)
    {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    // valid climbing 
    vector<vector<int>> num_ways = get_ways(stairs);

    // printing the number of ways to climb the stairs
    cout << num_ways.size() << " way";
    // adding the s 
    if (num_ways.size() > 1)
    {
        cout << "s";
    }
    cout << " to climb " << stairs << " stair";
    //adding the s 
    if (stairs > 1)
    {
        cout << "s";
    }
    cout << "." << endl;

    // display each way to climb the stairs
    display_ways(num_ways);

    return 0;

}
