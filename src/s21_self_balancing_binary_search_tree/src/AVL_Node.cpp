#include "../inc/AVL_Node.h"

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
