#include <iostream>
#include <string>
// #include "s21_key_value_storage/s21_key_value_storage.h"
#include "s21_hash_table.h"
#include "s21_self_balancing_binary_search_tree.h"


int main() {

	s21::Value v;

	v = { "Ivanov", "Ivan", "2020", "Rostov", "55" };

	s21::HashTable a;
	s21::SelfBalancingBinarySearchTree b;

	a.set("Hello, world", v, 5);
	b.set("Bye-bye, world", v, 7);

	std::cout << a.get("Hello, world") -> first_name << std::endl;
	std::cout << b.get("Bye-bye, world") -> last_name << std::endl;

	// KeyValueStorage<HashTable> a;
	// a.set("Hello, world", "Hello, world", 5);
	// std::cout << a.get("Hello, world") << std::endl;
    // KeyValueStorage<SelfBalancingTree> b;
    // b.set("Hello, world", "Hello, world", 5);
    // std::cout << b.get("Hello, world") << std::endl;

};
