// Class declaration for BinaryNode, a tree node object which holds
// pointers to its left and right child, as well as a data & search cost
// integer properties.
struct BinaryNode {
	BinaryNode* left;
	BinaryNode* right;
	int data;
	int search_cost;
	
	BinaryNode();
	BinaryNode(int);
	int depth(BinaryNode*);
};