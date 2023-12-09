#ifndef AVL_NODE
#define AVL_NODE

#include "../../s21_i_key_value_storage/s21_i_key_value_storage.h"
#include <functional>

using std::string;

namespace s21 {
	class AVL_Node {
	public:
		s21::Key		key;
		s21::Value		value;
		AVL_Node*		left;
		AVL_Node*		right;
		int				height;
		s21::TimeLimit	time_limit;

		AVL_Node(
			const s21::Key& k,
			const s21::Value& v,
			s21::TimeLimit = -1);
		~AVL_Node();
	};

	AVL_Node* 			insert(
		AVL_Node*		node,
		const Key&		key,
		const Value&	value,
		TimeLimit 		ttl = -1
	);

	AVL_Node* 			balance(AVL_Node* node);
	AVL_Node* 			find_node(AVL_Node* node, Key key);
	AVL_Node*			delete_node(AVL_Node* root, const Key& key);
	void 				traverse_tree( AVL_Node*, const std::function<void(AVL_Node*)>&);
}


#endif
