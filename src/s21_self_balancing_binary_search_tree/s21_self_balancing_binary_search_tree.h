#ifndef SELF_BALANCING_BINARY_SEARCH_TREE
#define SELF_BALANCING_BINARY_SEARCH_TREE
#include "inc/AVL_Node.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <map>
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

using std::string;
using std::vector;
using std::map;

namespace s21 {
	class SelfBalancingBinarySearchTree : public IKeyValueStorage {
	private:
		AVL_Node*			_root;
		map<Key, Value>		get_entries(void) const;

	public:
		SelfBalancingBinarySearchTree() : _root(nullptr) {}
		~SelfBalancingBinarySearchTree() { if (_root) delete _root; }
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
		// SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;

		void 				printTree(AVL_Node* root, int level = 0);

		/* * * * * * * * * * * * * * *   Methods  * * * * * * * * * * * * * * */

		void				set(const Key&, const Value&, TimeLimit = -1) override;
		const Value*		get(const Key& key) const noexcept override;
		bool				exists(const Key&) const noexcept override;
		bool				del(const Key&) noexcept override;
		void				update(const Key&, const Value&) override;
		std::vector<Key>	find(const Value&) const noexcept override;
		std::vector<Key>	keys(void) const noexcept override;
		void				rename(const Key&, const Key&) override;
		TimeLimit			ttl(const Key&) const noexcept override;

		// TODO: the lines below have no tests
		void 				save(const std::string&) const override;
		std::vector<Value>	showall() const noexcept override;
		void				print_tree();
	};

}

#endif
