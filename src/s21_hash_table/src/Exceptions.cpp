#include "../s21_hash_table.h"

namespace s21 {

	HashTable::HashTableException::HashTableException(const std::string &arg)
			: std::runtime_error(arg) {}

	HashTable::KeyException::KeyException(const std::string &arg)
			: HashTable::HashTableException(arg) {}

}
