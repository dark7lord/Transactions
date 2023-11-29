#include "AVL_Node.h"
#include <iostream>


AVL_Node::AVL_Node(const s21::Key& k, const s21::Value& v):
	key(k),
	value(v),
	left(nullptr),
	right(nullptr),
	height(1)
{}


AVL_Node::~AVL_Node() {
	delete left;
	delete right;
}
