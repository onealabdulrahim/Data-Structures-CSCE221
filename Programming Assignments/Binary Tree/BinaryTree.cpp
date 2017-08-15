#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "BinaryNode.h"
#include "BinaryTree.h"
using namespace std;

// constructor ensures null root node initialization
BinaryTree::BinaryTree() {root = NULL;}

/// Search Cost Calculation
/* Uses in-order traversal to visit every node and calculate its depth
subtracted from the root's depth. This gives how "deep" it is in the
tree.
This algorithm is recursive, similar to traversal operation.
After tree creation, call this to set all proper search costs.
@param r 	The currently visited node */
void BinaryTree::set_costs(BinaryNode* r) {
	if (r == NULL) { // base case
		return;
	}
	set_costs(r -> left);
	// search cost is how high the tree is minus how many nodes we have left
	r -> search_cost = (root -> depth(root)) - (r -> depth(r)) + 1;
	average_cost += r -> search_cost;
	set_costs(r -> right);
}

/// Loading Vector of Nodes
/* Uses in-order traversal to visit every node and insert it into a vector.
This algorithm is recursive, similar to traversal operation.
@param r 	The currently visited node */
void BinaryTree::set_vector(BinaryNode* r) {
	if (r == NULL) { // base case
		nodes.push_back(new BinaryNode());
		return;
	}
	set_vector(r -> left);
	// search cost is how high the tree is minus how many nodes we have left
	nodes.push_back(r);
	set_vector(r -> right);
}

/// Insert to tree
// inserts data in relation to a node
BinaryNode* BinaryTree::insert(int data, BinaryNode* r) {
	if (r == NULL) {
		BinaryNode* temp = new BinaryNode(data);
		++node_count; // since we are adding a new node
		temp -> search_cost++;
		return temp;
	}
	
	if (data < r -> data) {
		r -> left = insert(data, r -> left); // go left to keep things in order
	} else if (data > r -> data) {
		r -> right = insert(data, r -> right); // otherwise go right
	}
	
	r -> search_cost++;
	
	return r;
}

/// finds minimum node
BinaryNode* BinaryTree::find_min(BinaryNode *t) {
	while (t -> left != NULL) t = t->left;
	return t;
}

/// remove minimum
/* Removes the minimum node by recursively looking for leftmost node.
Since this node has no left child, we bypass this by calling right.
@param r	currently visited node */
BinaryNode* BinaryTree::remove_min(BinaryNode *r) {
	if (r -> left != NULL) {
		r -> left = remove_min(r -> left);
	} else {
		BinaryNode *temp = r;
		r = r -> right;
		delete temp;
	}
	return r;
}

/// node removal
BinaryNode* BinaryTree::remove(int x, BinaryNode *r) {
	if (x < r -> data)
		r -> left = remove(x, r -> left);
	else if (x > r -> data)
		r -> right = remove(x, r -> right);
	else if (r -> left != NULL && r -> right != NULL) {
		// item x is found; r has two children
		r -> data = find_min(r -> right) -> data;
		r -> right = remove_min(r -> right);
	} else { //r has only one child
		BinaryNode *temp = r;
		r = (r -> left != NULL) ? r -> left : r -> right;
		delete temp;
	}
	return r;
}


/// PREORDER TRAVERSAL
/* Visit the root node first, then its left children, then its right.
This algorithm is recursive, with base case if current node object is null
@param r	The particular root node */
void BinaryTree::print_preOrder(BinaryNode* r) {
	if (r == NULL) { // base case
		return;
	}
	cout << r -> data << "[" << r -> search_cost << "] ";
	print_preOrder(r -> left);
	print_preOrder(r -> right);
}

/// INORDER TRAVERSAL
/* Visit the left children, then the root, then its right children.
This algorithm is recursive, with base case if current node object is null
@param r	The particular root node */
void BinaryTree::print_inOrder(BinaryNode* r) {
	if (r == NULL) { // base case
		return;
	}
	print_inOrder(r -> left);
	cout << r -> data << "[" << r -> search_cost << "] ";
	print_inOrder(r -> right);
}

/// POSTORDER TRAVERSAL
/* Visit the right children, then the right children, then the root.
This algorithm is recursive, with base case if current node object is null
@param r	The particular root node */
void BinaryTree::print_postOrder(BinaryNode* r) {
	if (r == NULL) { // base case
		return;
	}
	print_postOrder(r -> left);
	print_postOrder(r -> right);
	cout << r -> data << "[" << r -> search_cost << "] ";
}


/// Level Order Print Helper
/* Uses queue to print binary node to a string. */
ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
	
    if (tree.root == NULL)  return os;
	
	// push root to queue
    queue<BinaryNode*> q;
    q.push(tree.root);
 
    while (1) {
        int count = q.size();
        if (count == 0)
            break;
		
		// as long as we have something in queue
        while (count > 0) {
            BinaryNode* temp = q.front();
			// if the node is empty, print X
			if (temp == NULL) {
				os << "X ";
			} else { // else print the data 
				os << temp -> data << " ";
			}
			
			// take the front node out
            q.pop();
			// check the children
			if (temp != NULL) {
				if (temp -> left != NULL) {
				q.push(temp -> left);
				} else {
					BinaryNode* node = NULL;
					q.push(node);
				}
				if (temp -> right != NULL) {
					q.push(temp -> right);
				} else {
					BinaryNode* node = NULL;
					q.push(node);
				}
			}
            count--;
        }
        os << endl;
    }
	return os;
}