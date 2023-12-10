#include <iostream>
#include <string>
#include "s21_hash_table.h"
#include "s21_self_balancing_binary_search_tree.h"
#include <unistd.h>

int main() {

	s21::Value ivan = { "Ivanov", "Ivan", "2020", "Rostov", "55" };
	s21::Value vika = { "Vika", "Victory", "2024", "Olimpia", "1 000 000" };

	s21::HashTable a;
	s21::SelfBalancingBinarySearchTree b;

	a.set("Ivan", ivan, 5);
	b.set("Vika", vika, 7);
	b.set("Ivan", ivan, 3);

	std::cout << a.get("Ivan") << std::endl;
	std::cout << b.get("Vika") << std::endl;

	try {
		b.upload("s21_self_balancing_binary_search_tree/tests/test_files/file_for_import");
		b.print_tree();
		b.save("file_output");
		std::cout << "Ivan seconds: "<< b.ttl("Ivan") << std::endl;
		std::cout << "Vika seconds: "<< b.ttl("Vika") << std::endl;
		std::cout << "Waiting 5s" << std::endl;
		sleep(5);
		std::cout << "Ivan seconds: "<< b.ttl("Ivan") << std::endl;
		std::cout << "Vika seconds: "<< b.ttl("Vika") << std::endl;
		b.print_tree();
		sleep(5);
		std::cout << "Ivan seconds: "<< b.ttl("Ivan") << std::endl;
		std::cout << "Vika seconds: "<< b.ttl("Vika") << std::endl;
		b.print_tree();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
};
