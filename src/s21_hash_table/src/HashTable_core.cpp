#include "../s21_hash_table.h"

namespace s21 {

	HashTable::HashTable() : currentBucketCount_(initialBucketCount_),
							 currentLoadCount_(0) {
		std::cout << "Create Hash Table - default constructor" << std::endl;
		table_ = new std::vector<std::list<Node>>(initialBucketCount_);
		std::cout << "Create Hash Table : capacity " << table_ -> capacity() << " size " << table_ -> size() << std::endl;
	}

	HashTable::HashTable(HashTable const& other) : currentBucketCount_(other.currentBucketCount_),
												   currentLoadCount_(other.currentLoadCount_) {
		std::cout << "Create Hash Table - copy constructor" << std::endl;
		table_ = new std::vector<std::list<Node>>(*other.table_);
	}

	HashTable::HashTable(HashTable&& other) noexcept : currentBucketCount_(other.currentBucketCount_),
	                                                   currentLoadCount_(other.currentLoadCount_) {
		std::cout << "Create Hash Table - move constructor" << std::endl;
		table_ = other.table_;
		other.table_ = nullptr;
	}

	HashTable& HashTable::operator=(const HashTable& other) {
		std::cout << "Copy Hash Table - copy operator" << std::endl;
		if (this != &other) {
			table_ = new std::vector<std::list<Node>>(*other.table_);
			currentBucketCount_ = other.currentBucketCount_;
			currentLoadCount_ = other.currentLoadCount_;
		}
		return *this;
	}

	HashTable& HashTable::operator=(HashTable&& other) noexcept {
		std::cout << "Move Hash Table - move operator" << std::endl;
		if(this != &other) {
			table_ = other.table_;
			other.table_ = nullptr;
			currentBucketCount_ = other.currentBucketCount_;
			currentLoadCount_ = other.currentLoadCount_;
		}
		return *this;
	}

	HashTable::~HashTable() {
		std::cout << "Destroy Hash Table - destructor" << std::endl;
		delete table_;
	}

	/*
	Standard boost realization of hash_code(std::string) function. The
	irrational golden ratio 0x9e3779b9 is used for generating non-collinear
	binary sequence.
	*/
	HashCode HashTable::hashCode_(const Key& key) noexcept {
		std::cout << "Get Hash Code - key " << key << std::endl;
		HashCode    seed = HashTable::hashSeed_;
		auto        first = key.begin();
		auto        last = key.end();

		for(; first != last; ++first) {
			seed ^= (std::size_t)(*first)
				+ 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}

	std::size_t HashTable::indexFor_(HashCode hash) const noexcept {
		std::cout << "Get Index - hash " << hash << std::endl;
		std::cout << "Get Index - Capacity " << table_ -> capacity() << std::endl;
		return hash & ((table_ -> capacity()) - 1);
	}

	double HashTable::currentLoadFactor_() const noexcept {
		return (double) currentLoadCount_ / (double) currentBucketCount_;
	}

	void HashTable::increaseTable_() {
		std::size_t	old_buckets_cnt = currentBucketCount_;
		std::list<Node>::iterator it;
		std::size_t new_index;
		std::cout << "increase table - capacity " << table_ -> capacity() << " size " << table_ -> size() << std::endl;

		if (currentBucketCount_ == maximumCapacity_) {
			return;
		}
		currentBucketCount_ *= 2;
		table_ -> reserve(currentBucketCount_);
		table_ -> insert(table_ -> end(), old_buckets_cnt, std::list<Node>());
		for (std::size_t bucket_num = 0; bucket_num < old_buckets_cnt; bucket_num++) {
			it = (*table_)[bucket_num].begin();
			while (it != (*table_)[bucket_num].end()) {
				new_index = indexFor_(it -> hash);
				if (new_index != bucket_num) {
					(*table_)[new_index].push_back(*it);
					it = (*table_)[bucket_num].erase(it);
				} else {
					it++;
				}
			}
		}
		std::cout << "increase table - capacity " << table_ -> capacity() << " size " << table_ -> size() << std::endl;
	}

} // namespace s21