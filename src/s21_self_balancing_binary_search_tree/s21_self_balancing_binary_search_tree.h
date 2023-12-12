#ifndef S21_SELF_BALANCING_BINARY_SEARCH_TREE
#define S21_SELF_BALANCING_BINARY_SEARCH_TREE
#include "inc/AVL_Node.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <map>
#include <set>
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

using std::string;
using std::vector;
using std::map;

namespace s21 {
	class SelfBalancingBinarySearchTree : public IKeyValueStorage {
	private:
		AVL_Node*			_root;
		std::set<AVL_Node*>	_nodes_with_TTL;
		void				check_nodes_with_TTL(void);

	public:
		SelfBalancingBinarySearchTree() : _root(nullptr) {}
		~SelfBalancingBinarySearchTree() { if (_root) delete _root; }
		SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree&);
		SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&);
		SelfBalancingBinarySearchTree& operator=(const SelfBalancingBinarySearchTree&);
		SelfBalancingBinarySearchTree& operator=(SelfBalancingBinarySearchTree&&) noexcept;
		void copy_tree(AVL_Node*& destination, const AVL_Node* source);
		void clear();

		/* * * * * * * * * * * * * * *   Methods  * * * * * * * * * * * * * * */

		void				set(const Key&, const Value&, TimeLimit = -1) override;
		const Value*		get(const Key& key) noexcept override;
		bool				exists(const Key&) noexcept override;
		bool				del(const Key&) noexcept override;
		void				update(const Key&, const Value&) override;
		std::vector<Key>	find(const Value&) noexcept override;
		std::vector<Key>	keys(void) noexcept override;
		void				rename(const Key&, const Key&) override;
		TimeLimit			ttl(const Key&) noexcept override;
		void 				save(const std::string&) override;
		std::vector<Value>	showall(void) noexcept override;
		void				print_tree(void);
	};

} // namespace s21

#endif // S21_SELF_BALANCING_BINARY_SEARCH_TREE
