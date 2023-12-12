#include "../s21_hash_table.h"

namespace s21 {

	bool HashTable::Node::is_expired() noexcept {
		if (this -> time_limit == -1) {
			return false;
		}
		std::time_t expired_time = this -> set_time + this -> time_limit;
		if (expired_time <= std::time(nullptr)) {
			return true;
		}
		return false;
	}

	/*
    Find first occurence with bigger or equal hash code than inserted to store
    nodes in sorted order.
    */
	std::list<HashTable::Node>::iterator
	HashTable::first_bigger_or_equal_hash_(const HashCode& hash,
										   std::list<HashTable::Node>& lst) noexcept {
		auto last = lst.end();

		for (auto first = lst.begin(); first != last; first++) {
			if (hash >= first -> hash) {
				return first;
			}
		}
		return last;
	}

	bool HashTable::check_key_exists_(const Key& key,
						              const HashCode& hash,
						              std::list<HashTable::Node>& lst,
									  std::list<HashTable::Node>::iterator& first) noexcept {
		auto last = lst.end();
		bool key_found = false;

		for (; first != last && hash == first -> hash; first++) {
			if (key == first -> key) {
				if (first -> is_expired()) {
					lst.erase(first);
					currentLoadCount_--;
					key_found = false;
				}
				key_found = true;
				break;
			}
		}
		return key_found;
	}

}