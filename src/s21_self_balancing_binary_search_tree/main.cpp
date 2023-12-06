// #inc "AVL_Node.h"
#include "s21_self_balancing_binary_search_tree.h"
#include <iostream>
// using std::string

int main() {
	s21::s21_self_balancing_binary_search_tree avl_tree;
	avl_tree.set("1", { "Ivanov", "Ivan", "2020", "Rostov", "55" });
	avl_tree.set("3", { "Burova", "Vika", "1996", "Piter", "40" });
	avl_tree.set("7", { "Magomed", "Ozdoev", "1985", "Sochi", "10" });
	avl_tree.set("4", { "Minato", "Hokage", "2001", "Konoha", "500" });

	return 0;
}
