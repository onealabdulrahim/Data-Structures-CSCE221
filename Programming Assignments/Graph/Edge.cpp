#include "Edge.hpp"

// Our graphs are unweighted, but the implementation
// is required. We will allow weight = 0

/// constructor
Edge::Edge(int start, int end, int weight)
	: start(start), end(end), weight(weight) {}

std::ostream& operator<<(std::ostream& out, const Edge& e) {
	out << e.end << " ";
}