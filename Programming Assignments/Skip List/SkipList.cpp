// from the man himself ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf

#include <vector>
#include <random>
#include <algorithm>
#include <limits>
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_LEVEL = 64; // global

struct Node {
	int data; // integer data
	vector<Node*> next; // vector of pointers to each level's right node
						 // the length of this vector is the max height of node
						 // the index indicates the current level
	int search_cost;
	Node(int data) : data(data) {
		for (int i = 0; i < MAX_LEVEL; ++i) {
			next.push_back(nullptr);
		}
	}
};

struct SkipList {
	Node* first;
	Node* last;
	int node_count;
	int level_count;
	int search_cost;
	
	/// default constructor
	SkipList() {
		node_count = 0;
		level_count = 1;
		search_cost = 0;
		first = new Node(numeric_limits<int>::min());
		Node* last = new Node(numeric_limits<int>::max());
		for (int i = 0; i < MAX_LEVEL; ++i) {
			first -> next[i] = last;
		}
	}
	
	/// flip a coin until tails
	/**
	This method counts and returns the number of heads flipped
	until tails was achieved.
	@return	result	count of heads before 1 tails*/
	int get_random_level() {
		int result = 1;
		while ((double) rand() / RAND_MAX < 0.5) {
			++result;
		}
		return result; // guaranteed below max?
	}
	
	/// search
	/**
	Searches for a particular node data value and returns the first node
	which contains this value. (In the default iteration algorithm of SkipList)
	@param	data	The value to search for
	@return 		The node which holds the value */
	Node* search(int data) {
		search_cost = 0;
		int& cost = search_cost;
		// good checks
		if (data == numeric_limits<int>::min()) {
			return first;
		}
		
		if (data == numeric_limits<int>::max()) {
			return last;
		}
		
		// start at the beginning of the skip list
		Node* current = first;
		int level = level_count;
		// continue as long as there is something to search for
		while (current -> next[level]) {
			// if the next number is too small, move forward to the right
			if (current -> next[level] -> data < data) {
				++cost;
				current = current -> next[level];
			// if the next number is a match, return this pointer to node
			} else if (current -> next[level] -> data == data) {
				return current -> next[level];
			// otherwise, if the next number is too big, "drop down"
			} else if (current -> next[level] -> data > data) {
				++cost;
				--level;
			}
		}
		return nullptr; // never reached
	}
	
	/// insert
	/**
	Inserts a node with data value into proper place in a randomized # of levels
	@param	data	The value to search for */
	void insert(int data) {
		// printing information
		int comp_count = 0;		
		
		// start at the beginning node
		Node* current = first;
		vector<Node*> updater(MAX_LEVEL); // holds nodes "to be updated" (see below)
		// capture the nodes whose next pointers need to be updated
		for (int i = MAX_LEVEL - 1; i >= 0; --i) {
			// iterator to find value up to current data
			// we assume no duplicates!
			while (current -> next[i] && current -> next[i] -> data < data) {
				++comp_count;
				current = current -> next[i];
			}
			// in fact, the index of "updater" is the current level next pointer
			// 		which requires updating
			updater[i] = current;
		}
		
		int new_level = get_random_level(); // PRNG for level count
		current = new Node(data); // recycle variable to hold new pointer to Node
		
		if (new_level > level_count) { // max level that we have any data
			level_count = new_level; // will assist with printing later
		}
		
		// finally, perform the pointer updates
		for (int i = 0; i < new_level; ++i) {
			// on a particular level, x will point to old pointer's next
			current -> next[i] = updater[i] -> next[i];
			// and the old pointer's next is now current
			updater[i] -> next[i] = current;
			
			// familiar insertion? i'm thinkin singly linked list! :)
		}
		
		cout << "Adding " << data << " to level: " << new_level << ", "
			 << comp_count << " comparisons" << endl;
		++node_count; // keep track of how many nodes we have
	}
	
	/// removal
	/**
	Removes a node with data value & fixes pointers to account for it
	@param	data	The value of the node to remove*/
	void remove(int data) {
		int comp_count = 0;
		Node* current = first; // start at the top
		vector<Node*> updater(MAX_LEVEL); // keep track of nodes that require updating
		for (int i = level_count; i >= 0; --i) {
			while (current -> next[i] -> data < data) { // keep iterating
				++comp_count;
				current = current -> next[i];
			}
			updater[i] = current; // place the rightmost reached node in updater
		}
		
		current = current -> next[0]; // move forward so we're on the desired node
		
		if (current -> data == data) { // if in fact, we made it
			for (int i = 0; i < level_count; ++i) { // iterate through the next pointers
				if (updater[i] -> next[i] != current) {
					break;
				}
				updater[i] -> next[i] = current -> next[i]; // reallocate next, just like SLL
			}
			delete current; // free pointer/memory
			while (level_count > 1 && first -> next[level_count] -> data == numeric_limits<int>::max()) {
				--level_count; // manage levels for better printing
			}
		}
		if (node_count <= 16) {
			cout << "#comps for removing: " << data << ": " << comp_count << endl;
		}
		--node_count;
	}
	
	int set_search_cost(int data) {
		Node* current = search(data);
		current -> search_cost = search_cost;
		return search_cost;
	}
	
};

ostream& operator<<(ostream& out, const SkipList& sl) {
	out << "Levels: " << sl.level_count << endl;
	for (int i = sl.level_count; i >= 0; --i) {
		Node* current = sl.first;
		while (current -> next[i]) {
			if (current -> data == numeric_limits<int>::min()) {
				out << "-∞" << " —— ";
			} else {
				out << current -> data << " —— ";
			}
			current = current -> next[i];
		}
		out << "∞" << endl;
	}
}

/// File IO
/* Reads a file for integers, returns a vector of ints with data.
@param filename		The name of the file to parse */
vector<int> read_file(string filename) {
	ifstream input;
	input.open(filename);
	string int_data;
	
	vector<int> result;
	
	if (input.is_open()) {
		while (input >> int_data) {
			result.push_back(stoi(int_data));
		}
	}
	
	return result;
}

int main() {
	srand(time(NULL));
	
	cout << "Enter a file name to parse (eg. \"3p\"): ";
	string filename = "";
	cin >> filename;
	SkipList sl;
	
	// make vector of ints to hold data from file
	// get data from file, load into vector one by one int
	vector<int> file = read_file("test_files/" + filename);
	
	for (int i = 0; i < file.size(); ++i) {
		sl.insert(file[i]);
	}
	int costs = 0;
	// once we got everything in there, then calc search costs
	for (int i = 0; i < file.size(); ++i) {
		costs += sl.set_search_cost(file[i]);
	}
	
	if (sl.node_count <= 16) {
		cout << sl;
	}	
	
	cout << "\n\nAverage insert cost: " << costs / sl.node_count << endl
		 << "Average delete cost: " << costs / sl.node_count << endl << endl << endl;
	
	
	for (int i = 1; i < file.size(); ++i) {
		sl.remove(file[i]);
	}
	
	
}