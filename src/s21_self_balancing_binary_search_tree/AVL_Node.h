#ifndef AVL_NODE
#define AVL_NODE

#include <string>
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

using std::string;

class AVL_Node {
public:
	s21::Key	key;
	s21::Value	value;
	AVL_Node*	left;
	AVL_Node*	right;
	int			height;

	AVL_Node(const s21::Key& k, const s21::Value& v);
	~AVL_Node();
};

// #inc "AVL_Node.tpp"
#endif
