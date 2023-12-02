#include "s21_hash_table.h"

namespace s21 {

	/*
	Save new node in appropriate bucket in sorted by hash order.
	Exception: the key already exists.
	*/
    void HashTable::set(const Key& key, const Value& val, TimeLimit time) {
        HashCode    		hash = hashCode_(key);
        std::size_t			index = indexFor_(hash);
        std::list<Node>&	bucket = (*table_)[index];

        std::cout << "Set New node - key " << key << std::endl;
        auto place_to_insert = first_bigger_or_equal_hash(hash, bucket);
		if (check_key_exists(key, hash, bucket, place_to_insert)) {
			throw HashTable::KeyException("The key already exists");
		}
		bucket.insert(place_to_insert, HashTable::Node({hash, key, val, time}));
        currentLoadCount_++;
        if (HashTable::currentLoadFactor_() >= initialLoadFactor_) {
            HashTable::increaseTable_();
        }
        std::cout << "Changed list index " << index << std::endl;
        std::cout << "New lst size " << (*table_)[index].size() << std::endl;
    }

    const Value* HashTable::get(const Key& key) const noexcept {
        HashCode    hash = hashCode_(key);
        std::size_t index = indexFor_(hash);
        auto		first = (*table_)[index].begin();
        auto		last = (*table_)[index].end();

        while (first != last && first -> hash <= hash) {
            if (hash == first -> hash && key == first -> key) {
                return &(first -> val);
            }
            first++;
        }
        return nullptr;
    }

	bool HashTable::exists(const Key& key) const noexcept {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash(hash, (*table_)[index]);

		return check_key_exists(key, hash, (*table_)[index], first);
	}

	std::size_t HashTable::size() const noexcept {
		return currentLoadCount_;
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
                          std::list<HashTable::Node>::iterator first) noexcept {
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

    HashTable& HashTable::operator=(HashTable const& other) {
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
		std::list<Node>::iterator it;
        delete table_;
    }

	HashTable::HashTableException::HashTableException(const std::string &arg)
        : std::runtime_error(arg) {}

    HashTable::KeyException::KeyException(const std::string &arg)
        : HashTable::HashTableException(arg) {}

	std::vector<Key> HashTable::keys(void) const noexcept {
		return std::vector<Key>();
	}
	void HashTable::rename(const Key&, const Key&) {}
	TimeLimit HashTable::ttl(const Key&) const noexcept {
		return TimeLimit();
	}
	std::vector<Key> HashTable::find(const Value&) const noexcept {
		return std::vector<Key>();
	}
//		std::vector<Value> showall(void) const noexcept ; //  согласовать использование итератора
	void HashTable::upload(const std::string&) {}

	bool HashTable::del(const Key &) noexcept {
		return false;
	}

	void HashTable::update(const Key &, const Value &) {

	}

}