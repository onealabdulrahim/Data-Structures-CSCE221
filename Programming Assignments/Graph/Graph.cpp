#include "Graph.hpp"

/// default constructor
Graph::Graph() {
	vertices.clear();
}

/// constructor adding first vertex
Graph::Graph(int first) {
	this -> vertices.push_back(new Vertex(first));
}

/// insertion
/**
Inserts a vertex into the graph's vertices linked list.
@param v	Pointer to vertex to be inserted */
void Graph::add_vertex(Vertex* v) {
	this -> vertices.push_back(v);
}

/// Topological Sort (implementing Kahn's Algorithm)
/**
Creates & prints a topological ordering of the DAG G.
We assume: input data is ordered and does not skip integers
I hate recursion, so I found this method is very clear! :-) */
void Graph::topological_order() {
    // initialize vector of 0's to store in-degrees of vertices
	// in-degree: number of edges directed at vertex
    vector<int> in_degree(vertices.size() + 1, 0);
 
    // store all in-degrees of vertices by traversing their edges
    // this time complexity defines this method at O(V+E) 
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i] -> edges.size(); ++j) {
			in_degree[vertices[i] -> edges[j].end]++;
		}
    }
	
    // enqueue all vertices which are of in-degree 0
	// if the graph is not DAG, queue is empty and methods below
	// will fail (never execute)
    queue<int> q;
	// start at 1 because of 0 index
    for (int i = 1; i <= vertices.size(); ++i) {
		if (in_degree[i] == 0) {
			q.push(i);
		}
	}
        
    // count the visited vertices
    int count = 0;
 
    vector<int> result;
 
    // dequeue in-degree 0 vertices, check children
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        result.push_back(front);
		
		// now check children vertices, since their in-degree decreases by 1
        for (int i = 0; i < vertices[front - 1] -> edges.size(); ++i) {
			// If in-degree becomes zero, add it to queue
            if (--in_degree[vertices[front - 1] -> edges[i].end] == 0) {
				q.push(vertices[front - 1] -> edges[i].end);
			}
		}
        ++count;
    }
 
    // if there was a cycle or the while loop was never entered, failed!
    if (count != vertices.size()) {
        cout << "Topological ordering failed!" << endl;
    }
 
    // Print topological order
    for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	
    cout << endl;
}

std::ostream& operator<<(std::ostream& out, const Graph& g) {
	for (int i = 0; i < g.vertices.size(); ++i) {
		out << *g.vertices[i];
	}
}