#include <iostream>
#include <string>
// #include "s21_key_value_storage/s21_key_value_storage.h"
#include "s21_hash_table.h"
#include "s21_self_balancing_binary_search_tree.h"


int main() {

	s21::Value v = { "Ivanov", "Ivan", "2020", "Rostov", "55" };

	s21::HashTable a;
	a.set("Hello, world", v, 5);
	std::cout << a.get("Hello, world") -> first_name << std::endl;


	// s21::SelfBalancingBinarySearchTree b;
	// std::cout << "----------------"<< std::endl;
	// b.set("10", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("20", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("30", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("40", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("50", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("60", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("70", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("0", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("15", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("33", v);
	// std::cout << "----------------"<< std::endl;
	// b.set("32", v);
	// std::cout << "----------------"<< std::endl;

	// b.del("01");
	// b.set("82", v);
	// b.set("64", v);
	// b.set("55", v);
	// b.set("45", v);
	// // b.del("45");
	// b.del("50");

	// b.printTree();

	// KeyValueStorage<HashTable> a;
	// a.set("Hello, world", "Hello, world", 5);
	// std::cout << a.get("Hello, world") << std::endl;
	// KeyValueStorage<SelfBalancingTree> b;
	// b.set("Hello, world", "Hello, world", 5);
	// std::cout << b.get("Hello, world") << std::endl;

};
