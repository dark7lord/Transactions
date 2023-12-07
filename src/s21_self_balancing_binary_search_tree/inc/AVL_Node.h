#ifndef AVL_NODE
#define AVL_NODE

#include <string>
#include "../../s21_i_key_value_storage/s21_i_key_value_storage.h"

using std::string;

class AVL_Node {
public:
	s21::Key		key;
	s21::Value		value;
	AVL_Node*		left;
	AVL_Node*		right;
	int				height;
	s21::TimeLimit	time_limit;

	AVL_Node(const s21::Key& k, const s21::Value& v, s21::TimeLimit = -1);
	~AVL_Node();
};

#endif
