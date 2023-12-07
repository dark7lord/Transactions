#ifndef S21_HASHTABLE_EXCEPTIONS
#define S21_HASHTABLE_EXCEPTIONS
#include "HashTable.h"

namespace s21 {

	struct HashTable::HashTableException : std::runtime_error {
		explicit HashTableException(const std::string &arg);
	};

	struct HashTable::KeyException : HashTableException {
		explicit KeyException(const std::string &arg);
	};

} // namespace s21

#endif //S21_HASHTABLE_EXCEPTIONS
