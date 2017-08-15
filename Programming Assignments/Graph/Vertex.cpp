#include "Vertex.hpp"

/// Def. Constructor
// sets the data label of the current vertex
Vertex::Vertex(int data) : data(data) {};

/// connect to
/**
"Connects" an edge to the vertex by appending a new edge pointer
to the vertex's edge list. @@!!@@Assumption that graph is unweighted@@!!@@
@param end	The integer corresponding to the end of the edge */
void Vertex::connect(int end, int weight) {
	// unweighted
	Edge temp(this -> data, end, weight);
	this -> edges.push_back(temp);
}

std::ostream& operator<<(std::ostream& out, Vertex& v) {
	out << "VERTEX " << v.data << ": ";
	for (int i = 0; i < v.edges.size(); ++i) {
		out << v.edges[i].end << " ";
	}
	out << endl;
}