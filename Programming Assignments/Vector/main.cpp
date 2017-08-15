/**
@Title A1: templated vector
@Author Oneal Abdulrahim
@Purpose To implement a vector class in C++
		 relative to the Array data structure
@Due Monday, September 12, 2016
@Files main.cpp	My_vec<char>.cpp My_vec<char>.h makefile
*/

#include "My_vec.cpp"
#include <iostream>
#include <stdexcept>

int main(){
    
// Please see report for screenshots of other datatypes.
// You are also free to change datatypes and values here, too.
// It is currently My_vec of booleans, but char, int, and double were tested
    
try {
    // define an object v of My_vec<char> type
	My_vec<bool> v;
    cout << "insert false at the rank 0 into the vector v" << endl;
	v.insert_at_rank(0, false);
	// use the overloaded operator << to display vector elements
	cout << v;
    // display the vector v size
	cout << "The size of v: " << v.get_size() << endl;
	
	int z = 2; // z is not defined in the main file
	cout << "insert true at the rank z=2 into the vector v" << endl;
	v.insert_at_rank(z, true);
	// use the overloaded operator << to display vector elements
	cout << v;
	// display the vector v size
	cout << "The size of v: " << v.get_size() << endl;

	cout << "insert true at the rank 10 into the vector v" << endl;
	v.insert_at_rank(10, true);
    // use the overloaded operator << to display vector elements
	cout << v;
    // display the vector v size
	cout << "The size of v: " << v.get_size() << endl;


	cout << "remove a bool at the rank 1 from the vector v" << endl;
	v.remove_at_rank(1);
	// use the overloaded operator << to display vector elements
	cout << v;
	// display the vector v size
	cout << "The size of v: " << v.get_size() << endl;

	
	cout << "replace a bool at the rank 0 with true" << endl;
	v.replace_at_rank(0, true);
	// use the overloaded operator << to display vector elements
	cout << v;
	// display the vector v size
	cout << "The size of v: " << v.get_size() << endl;

	
	cout << "create a copy v1 of the vector v using a copy constructor" << endl;
	My_vec<bool> v1 = v;
	// use the overloaded operator << to display the vector v1
	cout << v1;
    //replace a bool at the rank 2 of the vector v1 with true
	v1.replace_at_rank(2, true);
	cout << "use the overloaded operator << to display vector v1 elements" << endl;
	cout << v1;
	cout << "The size of v: " << v.get_size() << endl;


	// define an object v2 of My_vec<char> type
	My_vec<bool> v2;
	cout << "insert false at the rank 0 into the vector v2" << endl;
	v2.insert_at_rank(0, false);
	// use the overloaded operator << to display vector elements
	cout << v2;
    // display the vector v2 size
	cout << "The size of v: " << v.get_size() << endl;

    cout << "test the assignment operator and copy the vector v1 to v2 " << endl;
	v2 = v1;
    // use the overloaded operator << to display vector v2
	cout << v2;
    // display the vector v2 size
	cout << "The size of v: " << v.get_size() << endl;

    // test the function find_max_index using v2
	cout << "The max value is at v2[" << find_max_index(v2, v2.get_size()) << "]" << endl;
	
	
	// test the function sort_max using v2
	sort_max(v2);
	cout << "The sorted v2:" << endl;
	cout << v2;
	
	
	cout << "replace in the vector v2 a bool at the rank 14 with true" << endl;
	v2.replace_at_rank(14, true);
	cout << v2;

}

catch(exception &error) {
	cerr << "Error: " << error.what() << endl;
}
}

