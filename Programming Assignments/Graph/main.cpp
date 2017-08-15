#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Graph.hpp"

// Loads data from given filename into vector of integers
vector<int> get_file_data(string filename) {
	ifstream file;
	file.open(filename);
	string line;
	int current;
	vector<int> result;
	
	if (file.is_open()) {
		while (!file.eof()) {
			file >> current;
			result.push_back(current);
		}
	}
	
	file.close();
	return result;
}

// loads graph with vertices and their edges until -1 is passed,
// then makes a new vertex, etc.
Graph* build_graph(vector<int> data) {
	Graph* result = new Graph();
	Vertex* current = new Vertex(data[0]);	
	
	for (int i = 1; i < data.size(); ++i) {
		if (data[i] == -1) {
			++i;
			result -> add_vertex(current);
			current = new Vertex(data[i]);
		} else {
			current -> connect(data[i], 0);
		}
	}
	
	return result;	
}

int main(int argc, const char* argv[]) {
	try {
		vector<int> payload = get_file_data(argv[1]);
		Graph* myGraph = build_graph(payload);
		cout << *myGraph;
		cout << "Possible topological ordering: " << endl;
		myGraph -> topological_order();
	} catch(...) {
		cout << "\n\nInvalid file!! \nUsage:\n./main filename.txt\n\n";
		exit(1);
	}
}
