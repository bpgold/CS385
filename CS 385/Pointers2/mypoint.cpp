#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class MyPoint {
public:
	// Constructor that uses an initializer list.
	//copies x into x_, y into y_....
	MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { }

	// Methods that do not modify member variables should be declared const.
	void print_coords() const {
		cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
			 << setprecision(2) << z_ << ")" << endl;
	}

	// Mutator (setter).
	// setter is never const bc we want to cahnge the object 
	void set_x(int x) {
		x_ = x;
	}

	// Accessor (getter), declared const.
	//coonst bc we wont  change the object
	int get_x() const {
		return x_;
	}

private:
	// Member variables (fields). Use the trailing _ for these variables.
	int x_, y_;
	float z_;
}; // semicolon is required!

// Pass by reference, and using an iterator (which is an object
// that can be used essentially as if it were a pointer):
//loop in an object oriented way 
// special ++ for an iterator
void display_points(const vector<MyPoint> &points) {
	for(auto it = points.cbegin(); it != points.cend(); it++) {
		it->print_coords(); // Same as: (*it).print_coords();
	}
}

//size_t is an int type but bigger, biggest possible 
void display_points_v2(const vector<MyPoint> &points) {
	for(size_t i = 0; i < points.size(); i++) {
		points[i].print_coords(); //can use the vector like its an array 
	}
}

int main(void) {
	// Integers allocated on the stack (will be automatically deallocated
	// from the stack when the current function returns).
	int x, y;

	// Objects allocated on the stack (will be automatically deallocated
	// from the stack when the current function returns).
	MyPoint point1(5, 7, 1.9823412);
	MyPoint point2(1, 2, 3);
	MyPoint point3(4, 5, 6);
	point2.print_coords();

	//vectors similar to arrays
	vector<MyPoint> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

	vector<MyPoint> points_above_two;
	// &point is a reference; new name for the existing elemnt you are looking at in the loop 
	//auto takes the type automatically, here would be MyPoint 
	// For-each loop (using a reference so there is no copy):
	for(const auto &point : points) {
		if(point.get_x() > 2) {
			points_above_two.push_back(point);
		}
	}

	display_points(points_above_two);

	// Practice using standard in (STDIN)
	cout << "Input x: ";
	cin >> x;

	cout << "Input y: ";
	cin >> y;

	// Object allocated on the heap (must be explicitely deallocated in
	// your code using "delete" when you do not need to object anymore),
	// The pointer point4 itself is a local variable on the stack.
	MyPoint *point4 = new MyPoint(x, y, 7);
	// Calling the method using the pointer to the object.
	point4->print_coords(); // Same as: (*point4).print_coords();
	// Deallocating the object from the heap (this does not change the
	// pointer itself which is a local variable on the stack).
	// For every "new" in your code, there must be a corresponding
	// "delete", to make sure the heap is properly managed.
	delete point4;
	// if you dont delete a memory leak will occur 

	return 0;
}
