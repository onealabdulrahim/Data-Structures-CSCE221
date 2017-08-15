#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include <iostream>

class Edge {
public:
    int start;
    int end;
    int weight;
    
    Edge(int, int, int);
};

std::ostream& operator<<(std::ostream&, const Edge&);

#endif /* Edge_hpp */
