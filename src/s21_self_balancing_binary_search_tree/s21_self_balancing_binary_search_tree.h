#ifndef SELF_BALANCING_BINARY_SEARCH_TREE
#define SELF_BALANCING_BINARY_SEARCH_TREE
#include "AVL_Node.h"
#include <string>
#include <iostream>
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

namespace s21 {
	class SelfBalancingBinarySearchTree {
	private:
		AVL_Node* _root;

		int			getHeight(AVL_Node* node);
		void		updateHeight(AVL_Node* node);

		AVL_Node*	rotateLeft(AVL_Node* x);
		AVL_Node*	rotateRight(AVL_Node* y);
		AVL_Node*	balance(AVL_Node* node);
		AVL_Node*	insert(AVL_Node* node, const Key& key, const Value& value);
		AVL_Node*	minValueNode(AVL_Node*);
		AVL_Node*	deleteNode(AVL_Node*, Key);

	public:
		SelfBalancingBinarySearchTree() : _root(nullptr) {}
		~SelfBalancingBinarySearchTree() { if (_root) delete _root; }

		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
		// ~SelfBalancingBinarySearchTree() = default;

		AVL_Node* find_node(AVL_Node* node, Key key);
		void printTree(AVL_Node* root, int level = 0);

	public:			/*** Methods ***/
		void		set(Key, Value, TimeLimit = -1);
		Value		get(const Key& key);
		bool		exists(Key);
		bool		del(Key);

		// update
		// find
		// keys

		// rename

		// ttl
		// showall
		// upload
		// _export
		void printTree();


	};

}

#endif
