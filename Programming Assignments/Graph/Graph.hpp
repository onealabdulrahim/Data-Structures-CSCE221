#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

#include "Vertex.hpp"

using namespace std;

class Graph {
public:
    vector<Vertex*> vertices;
	Graph();
    Graph(int);
	void add_vertex(Vertex*);
    void display();
	void topological_order();
};

std::ostream& operator<<(std::ostream&, const Graph&);

#endif /* Graph_hpp */
