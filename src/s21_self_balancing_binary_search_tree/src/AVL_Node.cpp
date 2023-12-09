#include "../inc/AVL_Node.h"
#include <iostream>

namespace s21 {
	 AVL_Node::AVL_Node(const s21::Key& k, const s21::Value& v, s21::TimeLimit t):
		key(k),
		value(v),
		left(nullptr),
		right(nullptr),
		height(1),
		time_limit(t)
	{
		if (time_limit > 0) time_limit = time(0) + t; // timestamp
	}

	AVL_Node::~AVL_Node() {
		delete left;
		delete right;
	}

	using Node = AVL_Node;

	int get_height(Node* node) {
		return (node != nullptr) ? node->height : 0;
	}

	void update_height(Node* node) {
		if (!node) return;
		node->height = 1 + std::max(
			get_height(node->left), get_height(node->right)
		);
	}

	Node* rotate_left(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		y->left = x;
		update_height(x);
		update_height(y);

		return y;
	}

	Node* rotate_right(Node* y) {
		Node* x = y->left;
		y->left = x->right;
		x->right = y;
		update_height(y);
		update_height(x);

		return x;
	}

	bool is_left_heavy(Node* node) {
		return get_height(node->left) > get_height(node->right);
	}

	bool is_right_heavy(Node* node) {
		return get_height(node->right) > get_height(node->left);
	}

	Node* balance(Node* node) {
		update_height(node);

		int balanceFactor = get_height(node->left) - get_height(node->right);
		if (balanceFactor > 1) {
			if (is_right_heavy(node->left)) {
				node->left = rotate_left(node->left);
			}

			return rotate_right(node);
		}
		else if (balanceFactor < -1) {
			if (is_left_heavy(node->right)) {
				node->right = rotate_right(node->right);
			}

			return rotate_left(node);
		}

		return node;
	}

	Node* insert(
		Node*		node,
		const Key&		key,
		const Value&	value,
		TimeLimit 		ttl
	)
	{
		if (node == nullptr) {
			return new Node(key, value, ttl);
		}

		if (key < node->key) {
			node->left = insert(node->left, key, value, ttl);
		} else if (key > node->key) {
			node->right = insert(node->right, key, value, ttl);
		} else {
			throw std::out_of_range("The key" + key + "exists");
		}

		return balance(node);
	}

	Node* find_node(Node* node, Key key) {
		if (!node)					return nullptr;

		if (key == node->key)		return node;
		else if (key < node->key)	return find_node(node->left, key);
		else						return find_node(node->right, key);
	}

	Node* min_value_node(Node* node) {
		Node* current = node;

		while (current->left != nullptr)
			current = current->left;

		return current;
	}

	Node* delete_node(Node* root, const Key& key) {
		if (root == nullptr) return root;

		if		( key < root->key ) root->left = delete_node(root->left, key);
		else if	( key > root->key ) root->right = delete_node(root->right, key);
		else {
			if( (root->left == nullptr) || (root->right == nullptr) ) {

				Node *temp = root->left ? root->left : root->right;

				if (temp == nullptr) {
					root = nullptr;
				}
				else {
					*root = *temp;
				}

				delete(temp);
			}
			else {
				Node* temp = min_value_node(root->right);
				root->key = temp->key;
				root->value = temp->value;
				root->right = delete_node(root->right, temp->key);
			}
		}

		if (root == nullptr) return root;

		return balance(root);
	}

	void traverse_tree(
		Node* 								node,
		const std::function<void(Node*)>& 	func
	)
	{
		if (node != nullptr) {
			traverse_tree(node->left, func);
			func(node);
			traverse_tree(node->right, func);
		}
	}
}



