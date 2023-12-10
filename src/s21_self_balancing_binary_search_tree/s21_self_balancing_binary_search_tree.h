#ifndef S21_SELF_BALANCING_BINARY_SEARCH_TREE
#define S21_SELF_BALANCING_BINARY_SEARCH_TREE
#include "inc/AVL_Node.h"
#include <string>
#include <iostream>
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

namespace s21 {
	class SelfBalancingBinarySearchTree : public IKeyValueStorage {
	private:
		AVL_Node* _root;

		int					getHeight(AVL_Node* node);
		void				updateHeight(AVL_Node* node);
		
		AVL_Node*			rotateLeft(AVL_Node* x);
		AVL_Node*			rotateRight(AVL_Node* y);
		AVL_Node*			balance(AVL_Node* node);
		AVL_Node*			insert(AVL_Node* node, const Key& key, const Value& value);
		AVL_Node*			minValueNode(AVL_Node*);
		AVL_Node*			deleteNode(AVL_Node*, Key);

	public:
		SelfBalancingBinarySearchTree() : _root(nullptr) {}
		~SelfBalancingBinarySearchTree() { if (_root) delete _root; }

		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
		// ~SelfBalancingBinarySearchTree() = default;

		AVL_Node*	find_node(AVL_Node* node, Key key) const;
		void printTree(AVL_Node* root, int level = 0);

	public:					/*** Methods ***/
		void				set(const Key&, const Value&, TimeLimit = -1) override;
		const Value*		get(const Key& key) const noexcept override;
		bool				exists(const Key&) const noexcept override;
		bool				del(const Key&) noexcept override;
		void				update(const Key&, const Value&) override;
		std::vector<Key>	find(const Value&) const noexcept override;
		std::vector<Key>	keys(void) const noexcept override;

		void				rename(const Key&, const Key&) override;
		TimeLimit ttl(const Key&) const noexcept override;
		std::vector<Value> showall() const noexcept override;
		void upload(const std::string&) override;
		void save(const std::string&) const override;

		void printTree();


	};

} // namespace s21

#endif // S21_SELF_BALANCING_BINARY_SEARCH_TREE
