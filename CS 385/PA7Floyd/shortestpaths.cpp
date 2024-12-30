/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Breona Pizzuta and Alex Switaj
 * Version     : 1.0
 * Date        : 11/28/24
 * Description : Find the shortest path using Floyd's algorithm.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <climits> // to use LLONG_MAX
#include <fstream>
#include <algorithm>

using namespace std;
const long INF = LLONG_MAX;


/**
 * Initializes a matrix with default values.
 * Diagonal elements can be set to zero based on the `diag` flag.
 * use LLONG_MAX as placeholder for infinity 
 */
void initialize_matrix(long** matrix, int size, bool diag = true) {
    for (int i = 0; i < size; ++i) {
        matrix[i] = new long[size];
        fill(matrix[i], matrix[i] + size, LLONG_MAX);
        if (diag) {
            matrix[i][i] = 0;
        }
    }
}


/**
 * function that does floyd's algorithm based on pseudocode from class
*/
void floyd(long **matrix, int num_vertices, long **ivmatrix) {
    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if (matrix[i][k] != INF && matrix[k][j] != INF && matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j]; 
                    ivmatrix[i][j] = k;
                }
            }
        }
    }
}


/**
 * function to find the best path between a start and end vertex using recursion
*/
void reconstruct_path(int start, int end, long **ivmatrix, string &path) {
    if (ivmatrix[start][end] == INF) {
        if (!path.empty()){
            path += " -> ";
        }
        
        path += static_cast<char>(end + 'A');
        return;
    }
    int intermediate = ivmatrix[start][end];
    reconstruct_path(start, intermediate, ivmatrix, path);
    reconstruct_path(intermediate, end, ivmatrix, path);
    
}

/**
 * finds the shortest bath between each set of two vertices in the matrix using reconstruct_path
 * prints the vertices, the shortest distance, and the path taken to get between the vertices
 */
void bestpath(long **matrix, long **ivmatrix, int num_vertices) {
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            if (i != j) {
                if (matrix[i][j] == INF) {
                    cout << static_cast<char>(i+'A')<< " -> " << static_cast<char>(j+'A')<< ", distance: infinity, path: none" << endl;
                } else {
                    string path(1, static_cast<char>(i + 'A'));
                    reconstruct_path(i, j, ivmatrix, path);
                    
                    cout << static_cast<char>(i+'A') << " -> " << static_cast<char>(j+'A') << ", distance: "
                         << matrix[i][j] << ", path: " << path << endl;
                }
            } 
            else {
                cout << static_cast<char>(i+'A') << " -> " << static_cast<char>(j+'A') << ", distance: 0, path: " << static_cast<char>(i+'A') << endl;
            }
        }
    }
}


/**
 * Deletes the matrix (used when errors)
*/
void delete_matrix(long** matrix, int num_vertices) {
    for (int i=0; i<num_vertices; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

/**
* Using num of digits, n, to find the length 
*/
int len(long n) {
    int digits = 0;
    do {
        n /= 10;
        ++digits;
    } while (n);
    return digits;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, int num_vertices, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = use_letters ? len(max_val) :
		len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

/**
 * Main function to read input, error check and execute the Floyd algorithm.
 */
int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit); // Handle file read errors
    string line;
    long **matrix = nullptr;
    int num_vertices = 0;  // Declare here to make it available throughout main()

    try {
        unsigned int line_number = 1;

        while (getline(input_file, line)) {
            istringstream iss(line);
            string vertex1, vertex2;
            long weight;

            if (line_number == 1) {
                // Validate the number of vertices
                if (!(iss >> num_vertices) || num_vertices < 1 || num_vertices > 26) {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    input_file.close();
                    return 1;
                }
                // Initialize the distance matrix
                matrix = new long *[num_vertices];
                initialize_matrix(matrix, num_vertices);
            } else {
                iss.clear();
                // Validate the edge data format
                if (line.size() < 5 || !(iss >> vertex1 >> vertex2)) {
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                    input_file.close();
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }

                // Validate vertex 1
                if (vertex1.size() != 1 || vertex1[0] < 'A' || vertex1[0] >= 'A' + num_vertices) {
                    cerr << "Error: Starting vertex '" << vertex1 << "' on line " << line_number
                         << " is not among valid values A-" << (char)('A' + num_vertices - 1) << "." << endl;
                    input_file.close();
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }

                // Validate vertex 2
                if (vertex2.size() != 1 || vertex2[0] < 'A' || vertex2[0] >= 'A' + num_vertices) {
                    cerr << "Error: Ending vertex '" << vertex2 << "' on line " << line_number
                         << " is not among valid values A-" << (char)('A' + num_vertices - 1) << "." << endl;
                    input_file.close();
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }

                // Validate edge weight
                if (!(iss >> weight) || weight <= 0) {
                    cerr << "Error: Invalid edge weight '" << line.substr(4) << "' on line " << line_number << "." << endl;
                    input_file.close();
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }

                // Store edge in the matrix
                matrix[vertex1[0] - 'A'][vertex2[0] - 'A'] = weight;
            }
            line_number= line_number+1;
        }

        // Display the distance matrix
        display_table(matrix, "Distance matrix:", num_vertices);

        // Intermediate vertex matrix initialization
        long **ivmatrix = new long *[num_vertices];
        initialize_matrix(ivmatrix, num_vertices, false);

        // Execute Floyd algorithm
        floyd(matrix, num_vertices, ivmatrix);

        // Display results
        display_table(matrix, "Path lengths:", num_vertices);
        // Call the second display_table with use_letters set to true so that the table is printed with the letter values instead of numbers.
        display_table(ivmatrix, "Intermediate vertices:", num_vertices, true);  

        // find  paths
        bestpath(matrix, ivmatrix, num_vertices);

        // Clean up memory
        delete_matrix(matrix, num_vertices);
        delete_matrix(ivmatrix, num_vertices);

        // Close input file
        input_file.close();

    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'." << endl;
        if (matrix != nullptr) {
            delete_matrix(matrix, num_vertices);
        }
        return 1;
    }

    return 0;
}
