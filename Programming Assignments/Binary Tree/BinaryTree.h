// Class declarations for BinaryTree object, which organizes BinaryNode objects
struct BinaryTree {
	BinaryNode* root;
	int average_cost = 0;
	int node_count = 0;
	std::vector<BinaryNode*> nodes;
	
	BinaryTree();
	void set_costs(BinaryNode*);
	void set_vector(BinaryNode*);
	BinaryNode* insert(int, BinaryNode*);
	BinaryNode* find_min(BinaryNode*);
	BinaryNode* remove_min(BinaryNode*);
	BinaryNode* remove(int, BinaryNode*);
	void print_preOrder(BinaryNode*);
	void print_inOrder(BinaryNode*);
	void print_postOrder(BinaryNode*);
};

std::ostream& operator<<(std::ostream&, const BinaryTree&);

struct EmptyTreeException {};
