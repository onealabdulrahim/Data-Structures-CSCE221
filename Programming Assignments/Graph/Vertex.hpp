#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <list>
#include <vector>

#include "Edge.hpp"

using namespace std;

class Vertex {
public:
    int data;
    vector<Edge> edges;
    
    Vertex(int);
    
    void connect(int, int);
};

std::ostream& operator<<(std::ostream&, Vertex&);

#endif /* Vertex_hpp */
