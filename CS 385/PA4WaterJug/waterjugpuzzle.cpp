/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Breona Pizzuta and Alex Switaj
 * Date        : 10/15/24
 * Description : Water jug puzzle using breadth-first search
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>  // Include for reverse


using namespace std;


// Struct to represent the state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;


    State(int _a, int _b, int _c, string _directions) :
            a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }


    // String representation of state in tuple form.
    string to_string() const {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};




// Function to check if the current state matches the goal state.
bool is_goal_state(const State &curr, const State &goal) {
    //returns true if each current state matches its corresponding goal state
    return (curr.a == goal.a && curr.b == goal.b && curr.c == goal.c);
}




// Function to perform the pouring operation and return a new state.
State* pour_function(State curr, int curr_from_jug, int curr_to_jug, int capacity_from_jug, int capacity_to_jug, const string &from, const string &to) {
    // Calculate the amount to be poured.
    int amount_to_be_poured = 0;
    int room_left_to_jug = capacity_to_jug - curr_to_jug;
    if(curr_from_jug >= room_left_to_jug){
        amount_to_be_poured = room_left_to_jug;
    } else {
        amount_to_be_poured = curr_from_jug;
    }


    // If no water can be transferred, return nullptr so not creating arbitrary new states
    if (amount_to_be_poured == 0) {
        return nullptr;
    }


    // New state after pouring.
    // Checks each to and from state to make sure adding and subtracting water from the correct jugs
    int new_a = curr.a, new_b = curr.b, new_c = curr.c;
    if (from == "A"){
        new_a -= amount_to_be_poured;
        if (to == "B"){
            new_b += amount_to_be_poured;
        } else {
            new_c += amount_to_be_poured;
        }
    } else if (from == "B"){
        new_b -= amount_to_be_poured;
        if (to == "A"){
            new_a += amount_to_be_poured;
        } else {
            new_c += amount_to_be_poured;
        }
    } else if (from == "C"){
        new_c -= amount_to_be_poured;
        if (to == "A"){
            new_a += amount_to_be_poured;
        } else {
            new_b += amount_to_be_poured;
        }
    }


    // Create the new state.
    // New instruction is the string of the to state to the from state that is printed for pour when the state is reached. 
    string new_instruction;
	  //if the amount is only 1, prints gallon instead of gallons
        if(amount_to_be_poured == 1){
            new_instruction = "Pour " + to_string(amount_to_be_poured) + " gallon from " + from + " to " + to;
        } else {
            new_instruction = "Pour " + to_string(amount_to_be_poured) + " gallons from " + from + " to " + to;
        }
    State *new_state = new State(new_a, new_b, new_c, new_instruction);
    return new_state;
}


// BFS function to solve the Water Jug Puzzle.
void waterjugpuzzlebfs(int cap_a, int cap_b, int cap_c, int goal_a, int goal_b, int goal_c) {
    // Initialize the initial state and goal state.
    State* initial_state = new State(0, 0, cap_c, "Initial state");
    State goal_state(goal_a, goal_b, goal_c, "Goal state");


    //Create a queue to hold the states for the BFS 
    queue<State*> queue;
    //Create an unordered_set to hold all of the to_string() method representations of the states that are visited so that they can be tracked and then printed.
    unordered_set<string> visited;


    //create vector of State pointers to collect all created states to be able to delete them for memory management
    vector<State*> all_states;


    //add the initial state to each tracker
    queue.push(initial_state);
    visited.insert(initial_state->to_string());
    all_states.push_back(initial_state);


    //iterates through until the queue is empty
    while(!queue.empty()){
	  //create a State pointer curr that is the front value of the queue
        State* curr = queue.front();
        queue.pop();


	  //if the goal state has been reached, iterates through the printing methods
        if (is_goal_state(*curr, goal_state)){
		//create a vector of strings to track the solutions from goal state to initial state
            vector<string> solution_results;
            State* temp = curr;
		
		//adding the printing method based on the states that have been reached using their pointers to the parent. If they don’t have a parent State, they are not included, as they have not been reached. 
            while(temp->parent != nullptr){
                solution_results.push_back(temp->directions + ". " + temp->to_string());
		    //Since the solution_results is being appended from goal_state to initial_state, temp is reassigned to its parent and so on.
                temp = temp->parent;
            }
            //Reverse switches the order of the results so that they are from initial state to goal state
            reverse(solution_results.begin(), solution_results.end());
		//prints the initial state
            cout << "Initial state. " << initial_state->to_string() << endl;
		//for each pour that was tracked in solution_results, prints the string describing that pour and its resulting state
            for (const string &each_pour : solution_results){
                cout << each_pour << endl;
            }
           
            //remove all of the extra states that aren't needed anymore
            for (State* state : all_states){
                delete state;
            }
            return;
        }


	  //Goes through each pour attempt in order to create the next_states that can be reached


	  //Does the pour function for the set type of pour
        State *next_state = pour_function(*curr, curr->c, curr->a, cap_c, cap_a, "C", "A");
	  //if the state isn’t null and if it hasn’t been visited adds it
        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);
        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }
        //Does the pour function for the set type of pour
        next_state = pour_function(*curr, curr->b, curr->a, cap_b, cap_a, "B", "A");
	  //if the state isn’t null and if it hasn’t been visited adds it


        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);


        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }


	  //Does the pour function for the set type of pour
        next_state = pour_function(*curr, curr->c, curr->b, cap_c, cap_b, "C", "B");
	  //if the state isn’t null and if it hasn’t been visited adds it
        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);
        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }


	  //Does the pour function for the set type of pour
        next_state = pour_function(*curr, curr->a, curr->b, cap_a, cap_b, "A", "B");
	  //if the state isn’t null and if it hasn’t been visited adds it
        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);
        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }


	  //Does the pour function for the set type of pour
        next_state = pour_function(*curr, curr->b, curr->c, cap_b, cap_c, "B", "C");
	  //if the state isn’t null and if it hasn’t been visited adds it
        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);
        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }


	  //Does the pour function for the set type of pour
        next_state = pour_function(*curr, curr->a, curr->c, cap_a, cap_c, "A", "C");
	  //if the state isn’t null and if it hasn’t been visited adds it
        if (next_state != nullptr && visited.find(next_state->to_string()) == visited.end()) {
	      //sets the parent of next_state equal to the saved curr State
            next_state->parent = curr;
		//adds the next_state to each tracker
            queue.push(next_state);
            visited.insert(next_state->to_string());
            all_states.push_back(next_state);
        } else {
		//if the state is not needed, deletes the created state
            delete next_state;
        }
    }


    //prints no solution if the goal_state was never reached
    cout << "No solution." << endl;
    //delete all of the old states that aren't needed anymore
    for (State* state : all_states){
        delete state;
    }
    return;
}


int main(int argc, char *const argv[])
{
    istringstream iss;
    string str;
    int capacityA, capacityB, capacityC, goalA, goalB, goalC;


	//checks if there is the wrong number of arguments 
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
	//checks for invalid capacity of A
    iss.str(argv[1]);
    if (!(iss >> capacityA) || capacityA <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();


	//checks for invalid capacity of B
    iss.str(argv[2]);
    if (!(iss >> capacityB) || capacityB <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();


	//checks for invalid capacity of C
    iss.str(argv[3]);
    if (!(iss >> capacityC) || capacityC <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();


 //checks for invalid goal of A
    iss.str(argv[4]);
    if (!(iss >> goalA) || goalA < 0)
    {
        cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();


//checks for invalid goal of B
    iss.str(argv[5]);
    if (!(iss >> goalB) || goalB < 0)
    {
        cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();


//checks for invalid goal of C
    iss.str(argv[6]);
    if (!(iss >> goalC) || goalC < 0)
    {
        cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();


// checks if the goal is greater than the capacity of a
    iss.str(argv[1]);
    if (goalA > capacityA)
    {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    iss.clear();


// checks if the goal is greater than the capacity of b
    iss.str(argv[2]);
    if (goalB > capacityB)
    {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    iss.clear();


// checks if the goal is greater than the capacity of c
    iss.str(argv[3]);
    if (goalC > capacityC)
    {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    iss.clear();


// checks if the total of the goals equals the capacity
    if (capacityC != (goalA + goalB + goalC))
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    // Solve the water jug puzzle.
    waterjugpuzzlebfs(capacityA, capacityB, capacityC, goalA, goalB, goalC);
    return 0;
}