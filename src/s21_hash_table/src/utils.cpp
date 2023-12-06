#include "../s21_hash_table.h"

namespace s21 {

	/*
    Find first occurence with bigger or equal hash code than inserted to store
    nodes in sorted order.
    */
	std::list<HashTable::Node>::iterator
	first_bigger_or_equal_hash(const HashCode& hash,
							   std::list<HashTable::Node>& lst) noexcept {
		std::cout << "Get Place for insert - hash " << hash << std::endl;
		auto last = lst.end();

		for (auto first = lst.begin(); first != last; first++) {
			if (hash >= first -> hash) {
				return first;
			}
		}
		return last;
	}

	bool check_key_exists(const Key& key,
						  const HashCode& hash,
						  const std::list<HashTable::Node>& lst,
						  std::list<HashTable::Node>::iterator& first) noexcept {
		std::cout << "Check suspicious hash - hash " << hash << std::endl;
		auto last = lst.end();
		bool key_found = false;

		for (; first != last && hash == first -> hash; first++) {
			if (key == first -> key) {
				key_found = true;
				break;
			}
		}
		return key_found;
	}

}