#include "s21_hash_table.h"
#include "s21_self_balancing_binary_search_tree.h"

int main() {

	s21::Value v = { "Ivanov", "Ivan", "2020", "Rostov", "55" };
	s21::Value v2 = { "Karai", "Oruki", "1914", "Okinawa", "5500" };

	s21::HashTable a;
	a.set("Hello, world", v, 5);
	std::cout << a.get("Hello, world") -> first_name << std::endl;


	std::cout << "----------------"<< std::endl;
	std::cout << "Testing tree"<< std::endl;
	std::cout << "----------------"<< std::endl;
	s21::SelfBalancingBinarySearchTree tree;
	tree.set("10", v);
	tree.set("82", v);
	tree.set("64", v);
	tree.set("6", v);
	tree.set("1", v);
	tree.update("10", v2);
	tree.del("82");
	tree.set("100", v);
	tree.set("101", v);
	tree.printTree();

};
