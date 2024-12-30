#include <iostream>
#include <limits>
#include <queue>
#include <algorithm> // for max
using namespace std;

struct Node {
	Node *left, *right, *parent;
	int data, depth;

	Node(Node *parent, int depth, int data) :
		left{nullptr}, right{nullptr}, parent{parent},
		data{data}, depth{depth} { }
};

// O(tree height) (and the tree height is O(n))
Node* insert_helper(Node **pnode, int x, Node *parent, int depth) {
	if(*pnode == nullptr) {
		return *pnode = new Node(parent, depth, x);
	}
	if((*pnode)->data == x) {
		return nullptr;
	}
	if(x < (*pnode)->data) {
		return insert_helper(&(*pnode)->left, x, *pnode, depth + 1);
	} else {
		return insert_helper(&(*pnode)->right, x, *pnode, depth + 1);
	}
}

Node* insert(Node **pnode, int x) {
	return insert_helper(pnode, x, nullptr, 0);
}

// Θ(n)
void display_sideways(Node *node) {
	if(node != nullptr) {
		display_sideways(node->right);
		if(node->depth == 0) {
			cout << "-> ";
		} else {
			cout << "   ";
		}
		for(int i = 0; i < node->depth; ++i) {
			cout << "   ";
		}
		cout << node->data << endl;
		display_sideways(node->left);
	}
}

// O(tree height) (and the tree height is O(n))
Node* find(Node *node, int x) {
	if(node == nullptr) {
		return nullptr;
	}
	if(node->data == x) {
		return node;
	}
	if(x < node->data) {
		return find(node->left, x);
	} else {
		return find(node->right, x);
	}
}

// Sum all integers in the BST
// Θ(n)
int sum(Node *node) {
	if(node == nullptr) {
		return 0;
	} else {
		return node->data + sum(node->left) + sum(node->right);
	}
}

// Θ(n)
void decrement_depths(Node *node) {
	if(node != nullptr) {
		node->depth--;
		decrement_depths(node->left);
		decrement_depths(node->right);
	}
}

// Deletes and returns as result the minimum node in the non-empty tree.
// Since the tree is non-empty, such minimum node must exist.
// This code is similar to findMin except that we do not have to test
// the Null case since we know that the tree is non-empty.
// O(tree height) (and the tree height is O(n))
Node* delete_min(Node **pnode) {
	if((*pnode)->left == nullptr) {
		// current node is the minimum node, remove it from the tree and return it
		Node *min = *pnode;
		*pnode = min->right;
		if(min->right != nullptr) {
			min->right->parent = min->parent;
		}
		decrement_depths(min->right);
		return min;
	} else {
		// Keep moving down-left
		return delete_min(&(*pnode)->left);
	}
}

// O(tree height) (and the tree height is O(n))
bool delete_node(Node **pnode, int x) {
	if(*pnode == nullptr) {
		// Cannot find x, deletion fails
		return false;
	}
	if((*pnode)->data == x) {
		// Case 1: the node is a leaf
		// Note: this case is in fact a special case of the next one (case 2-a
		// or case 2-b) so this code could be merged with the next case.
		// We keep this case separate here for clarity.
		if((*pnode)->left == nullptr && (*pnode)->right == nullptr) {
			delete *pnode;
			*pnode = nullptr;
			return true;
		}
		// Case 2-a: the node has one left child
		if((*pnode)->left != nullptr && (*pnode)->right == nullptr) {
			Node *tmp = *pnode;
			*pnode = tmp->left;
			tmp->left->parent = tmp->parent;
			decrement_depths(tmp->left);
			delete tmp;
			return true;
		}
		// Case 2-b: the node has one right child
		if((*pnode)->left == nullptr && (*pnode)->right != nullptr) {
			Node *tmp = *pnode;
			*pnode = tmp->right;
			tmp->right->parent = tmp->parent;
			decrement_depths(tmp->right);
			delete tmp;
			return true;
		}
		// Case 3: the node has two children
		// We replace the node with the minimum node in the right subtree
		// (The maximum node in the left subtree would work too.)
		if((*pnode)->left != nullptr && (*pnode)->right != nullptr) {
			Node *tmp = *pnode;
			// Find the smallest node in the right subtree:
			Node *min = delete_min(&tmp->right);
			// Replace the node with the min:
			min->parent = tmp->parent;
			min->depth = tmp->depth;
			min->left = tmp->left;
			min->right = tmp->right;
			*pnode = min;
			min->left->parent = min;
			// If min used to be the right child of tmp then there
			// is no right child anymore, so we must test this.
			if(min->right != nullptr) {
				min->right->parent = min;
			}
			delete tmp;
			return true;
		}
	}
	if(x < (*pnode)->data) {
		return delete_node(&(*pnode)->left, x);
	} else {
		return delete_node(&(*pnode)->right, x);
	}
}

// Θ(n)
void delete_bst(Node *node) {
	if(node != nullptr) {
		delete_bst(node->left);
		delete_bst(node->right);
		delete node;
	}
}

// Create a balanced BST from a sorted array.
// Θ(n)
Node* create_bst_helper(int data[], int low, int high, Node *parent, int depth) {
	if(low > high) {
		return nullptr;
	}
	int mid = low + (high - low) / 2;
	Node *new_node = new Node(parent, depth, data[mid]);
	new_node->left = create_bst_helper(data, low, mid - 1, new_node, depth + 1);
	new_node->right = create_bst_helper(data, mid + 1, high, new_node, depth + 1);
	return new_node;
}

Node* create_bst(int data[], int length) {
	return create_bst_helper(data, 0, length - 1, nullptr, 0);
}

/* We need min and max to ensure that the binary search tree property
   is respected by the tree: data values in the tree must increase
   from left to right.  For example, in the tree:
         5
       /   \
      3     6
    /   \
   2     4
   we need to make sure that 4 is bigger than 3 but also less than 5.
   O(n)
 */
bool is_bst_helper(Node *node, int min, int max) {
	//check empty
	if(node == nullptr) {
		return true;
	}
	if(node->data <= min || node->data >= max) {
		return false;
	}
	return is_bst_helper(node->left, min, node->data) &&
			is_bst_helper(node->right, node->data, max);
}

bool is_bst(Node *tree) {
	return is_bst_helper(tree, std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());
}

// O(tree height)
Node* lowest_common_ancestor(Node *p, Node *q) {
	if(p == nullptr || q == nullptr) {
		return nullptr;
	}
	if(p == q) {
		return p;
	}
	if(p->depth > q->depth) {
		return lowest_common_ancestor(p->parent, q);
	}
	if(p->depth < q->depth) {
		return lowest_common_ancestor(p, q->parent);
	}
	return lowest_common_ancestor(p->parent, q->parent);
}

// Similar to breadth-first search in a graph. Note that this algorithm is
// not recursive because we need to count all the nodes at the same depth
// in many different parts of the tree at the same time.
// Θ(n)
int max_width(Node *node) {
	if(node == nullptr) {
		return 0;
	}
	int max_width = 0;
	queue<Node*> q;
	q.push(node);

	// Every time around the while loop, the queue contains all the nodes
	// at the current depth, starting from the depth of the root.
	while(!q.empty()) {
		int width = q.size(); // width of current level
		max_width = max(max_width, width);
		// Remove from the queue all the nodes from the current level and add
		// all their children (if any) to get all the nodes for the next level.
		for(int i = 0; i < width; i++) {
			Node *current = q.front();
			q.pop();
			if(current->left != nullptr) {
				q.push(current->left);
			}
			if(current->right != nullptr) {
				q.push(current->right);
			}
		}
	}
	return max_width;
}

// Find the node with the smallest value (so the leftmost node).
// O(tree height)
Node* find_min(Node *node) {
	if(node == nullptr) {
		return nullptr;
	}
	if(node->left == nullptr) {
		return node;
	} else {
		// Keep moving down-left
		return find_min(node->left);
	}
}

/* Finds the successor of a node: the node containing the value which
   is the next higher one relative to the value in the argument node.
         7
       /   \
      3     9
    /   \
   1     5
   For example 5 is the successor of 3 and 7 is the successor of 5.
   O(tree height)
 */
Node* successor(Node *node) {
	if(node == nullptr) {
		return nullptr;
	}
	// If the node has a right subtree then the successor of the node
	// is the node with the smallest value in the right subtree.
	if(node->right != nullptr) {
		return find_min(node->right);
	}
	// Otherwise we move up the parent links as long as each node is its
	// parent's right child. When a node is the left child of its parent,
	// the parent of that node is the successor of the original node.
	Node *parent = node->parent;
	while(parent != nullptr && node == parent->right) {
		node = parent;
		parent = node->parent;
	}
	// The following loop works as well, based on the values in the nodes:
	//while(parent != nullptr && parent->data < node->data) {
	//	node = parent;
	//	parent = node->parent;
	//}
	// At this point either parent is NULL (so there is no successor)
	// or the original node is the biggest value in the left subtree of
	// parent and therefore parent is the successor of the original node.
	return parent;
}

int main(int argc, const char *argv[]) {
	Node *bst1 = nullptr;
	insert(&bst1, 3);
	insert(&bst1, 5);
	insert(&bst1, 2);
	display_sideways(bst1);
	cout << endl;
	cout << "finding " << find(bst1, 5)->data << endl;
	cout << "sum is " << sum(bst1) << endl;
	cout << "deleting 3:" << endl << endl;
	delete_node(&bst1, 3);
	display_sideways(bst1);
	cout << endl;
	cout << "deleting 5:" << endl << endl;
	delete_node(&bst1, 5);
	display_sideways(bst1);
	cout << endl;
	delete_bst(bst1);
	bst1 = nullptr;

	int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	Node *bst2 = create_bst(data, 15);
	display_sideways(bst2);
	cout << endl << "Is BST? " << (is_bst(bst2) ? "yes" : "no") << endl << endl;

	Node *lca = lowest_common_ancestor(find(bst2, 6), find(bst2, 11));
	cout << "Lowest common ancestor of 6 and 11: " << lca->data << endl << endl;

	cout << "bst2 has a max width of " << max_width(bst2) << endl << endl;

	cout << "successor of 8 is " << successor(find(bst2, 8))->data << endl;
	cout << "successor of 7 is " << successor(find(bst2, 7))->data << endl << endl;

	delete_bst(bst2);
	return 0;
}
