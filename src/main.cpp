#include <iostream>
#include <string>
// #inc "s21_key_value_storage/s21_key_value_storage.h"
#include "include/HashTable.h"
#include "s21_self_balancing_binary_search_tree.h"


int main() {

	s21::Value ivan = { "Ivanov", "Ivan", "2020", "Rostov", "55" };
	s21::Value vika = { "Vika", "Victory", "2024", "Olimpia", "1000" };

	s21::HashTable a;
	s21::SelfBalancingBinarySearchTree b;

	a.set("Ivan", ivan, 5);
	b.set("Vika", vika, 7);

	std::cout << a.get("Ivan") << std::endl;
	std::cout << b.get("Vika") << std::endl;

};
