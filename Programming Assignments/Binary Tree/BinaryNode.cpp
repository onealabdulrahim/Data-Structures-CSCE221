#include <iostream>
#include <stdexcept>
#include "BinaryNode.h"
using namespace std;

// default constructor
BinaryNode::BinaryNode() {
	data = -1;
	search_cost = 0;
	left = NULL;
	right = NULL;
}

// constructor
BinaryNode::BinaryNode(int data) : data(data) {
	left = NULL;
	right = NULL;
}

// calculates the depth of a BinaryNode
int BinaryNode::depth(BinaryNode* r) {
	if (r == NULL) {
		return 0;
	} else {
		int left_depth = depth(r -> left);
		int right_depth = depth(r -> right);
		
		// if the right tree depth is greater
		if (left_depth < right_depth) {
			return right_depth + 1; // return right depth + 1
		}
		return left_depth + 1; // otherwise return left depth  + 1
	}
}