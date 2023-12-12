#include "../s21_hash_table.h"

namespace s21 {

	/*
	Save new node in appropriate bucket in sorted by hash order.
	Exception: the key already exists.
	*/
    void HashTable::set(const Key& key, const Value& val, TimeLimit time_limit) {
        HashCode    		hash = hashCode_(key);
        std::size_t			index = indexFor_(hash);
        std::list<Node>&	bucket = (*table_)[index];

        std::cout << "Set New node - key " << key << std::endl;
        auto place_to_insert = first_bigger_or_equal_hash_(hash, bucket);
		if (check_key_exists_(key, hash, bucket, place_to_insert)) {
			throw IKeyValueStorage::KeyExistsException();
		}
		if (time_limit == 0) {
			return;
		}
		bucket.insert(
			place_to_insert,
			HashTable::Node({hash, key, val, time_limit, std::time(nullptr)}));
        currentLoadCount_++;
        if (HashTable::currentLoadFactor_() >= initialLoadFactor_) {
            HashTable::increaseTable_();
        }
        std::cout << "Changed list index " << index << std::endl;
        std::cout << "New lst size " << (*table_)[index].size() << std::endl;
    }

	/*
	Get pointer to Value under certain key. Returns nullptr if key does not exist.
	*/
    const Value* HashTable::get(const Key& key) noexcept {
        HashCode    hash = hashCode_(key);
        std::size_t index = indexFor_(hash);
        auto		first = first_bigger_or_equal_hash_(hash, (*table_)[index]);

		if (check_key_exists_(key, hash, (*table_)[index], first)) {
			return &(first -> val);
		}
		return nullptr;
    }

	/*
	 Check the key existing.
	 */
	bool HashTable::exists(const Key& key) noexcept {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash_(hash, (*table_)[index]);

		return check_key_exists_(key, hash, (*table_)[index], first);
	}

	/*
	 Deletes key and value from storage. Returns an indicator of success deletion.
	 */
	bool HashTable::del(const Key& key) noexcept {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash_(hash, (*table_)[index]);

		if (check_key_exists_(key, hash, (*table_)[index], first)) {
			(*table_)[index].erase(first);
			currentLoadCount_--;
			return true;
		}
		return false;
	}

	void HashTable::update(const Key& key, const Value& val) {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash_(hash, (*table_)[index]);

		if (check_key_exists_(key, hash, (*table_)[index], first)) {
			first -> val = val;
		} else {
			throw IKeyValueStorage::KeyNotExistsException();
		}
	}

	/*
	Returns a vector of the existing keys.
	*/
	std::vector<Key> HashTable::keys() noexcept {
		std::vector<Key> res;
		std::list<Node>::iterator first;

		for (std::list<Node>& bucket : *table_) {
			first = bucket.begin();
			while (first != bucket.end()) {
				if (first -> is_expired()) {
					first = bucket.erase(first);
					currentLoadCount_--;
				} else {
					res.push_back(first -> key);
				}
				first++;
			}
		}
		return res;
	}

	/*
	Rename and replace a matched new key or create new node.
	*/
	void HashTable::rename(const Key& old_key, const Key& new_key) {
		HashCode    old_hash = hashCode_(old_key);
		std::size_t old_index = indexFor_(old_hash);
		auto		old_first = first_bigger_or_equal_hash_(old_hash, (*table_)[old_index]);
		HashCode    new_hash = hashCode_(new_key);
		std::size_t new_index = indexFor_(new_hash);
		auto		new_first = first_bigger_or_equal_hash_(new_hash, (*table_)[new_index]);

		std::cout << old_key << " " << new_key << std::endl;
		if (old_key == new_key) {
			return;
		}
		if (!check_key_exists_(old_key, old_hash, (*table_)[old_index], old_first)) {
			throw IKeyValueStorage::KeyNotExistsException();
		}
		if (check_key_exists_(new_key, new_hash, (*table_)[new_index], new_first)) {
			std::cout << "exists" << std::endl;
			new_first -> val = old_first -> val;
			currentLoadCount_--;
		} else {
			std::cout << "not exists" << std::endl;
			(*table_)[new_index].insert(
				new_first,
				HashTable::Node({new_hash, new_key,
					old_first -> val, old_first -> time_limit, old_first -> set_time}));
		}
		(*table_)[old_index].erase(old_first);
	}

	TimeLimit HashTable::ttl(const Key& key) noexcept {
		HashCode    hash = hashCode_(key);
        std::size_t index = indexFor_(hash);
        auto		first = first_bigger_or_equal_hash_(hash, (*table_)[index]);

		if (check_key_exists_(key, hash, (*table_)[index], first)) {
			if (first -> time_limit != -1) {
				return ((std::time_t)(first -> time_limit) +
					first -> set_time - std::time(nullptr));
			}
		}
		return -1;
	}

	std::vector<Key> HashTable::find(const Value& val) noexcept {
		std::vector<Key> res;
		std::list<Node>::iterator first;

		for (std::list<Node>& bucket : *table_) {
			first = bucket.begin();
			while (first != bucket.end()) {
				if (!(first -> val == val)) {
					first++;
					continue;
				}
				if (first -> is_expired()) {
					first = bucket.erase(first);
					currentLoadCount_--;
				} else {
					std::cout << "Все идет по плану" << std::endl;
					res.push_back(first -> key);
				}
				first++;
			}
		}

		return res;
	}

	std::vector<Value> HashTable::showall() noexcept {
		std::vector<Value> res;
		std::list<Node>::iterator first;

		for (std::list<Node>& bucket : *table_) {
			first = bucket.begin();
			while (first != bucket.end()) {
				if (first -> is_expired()) {
					first = bucket.erase(first);
					currentLoadCount_--;
				} else {
					res.push_back(first -> val);
				}
				first++;
			}
		}
		return res;
	}

	void HashTable::upload(const std::string&) {}

	void HashTable::save(const std::string& filename) {
		std::ofstream output_file(filename, std::ios::trunc);
		std::vector<Key> all_keys;
		const Value* val;

		if (output_file.is_open()) {
			all_keys = keys();
			for (const Key& key: all_keys) {
				val = get(key);
				if (val != nullptr) {
					output_file << std::quoted(key) << " " << *val << std::endl;
				}
			}
			output_file.close();
		} else {
			throw IKeyValueStorage::CantOpenFile(filename);
		}
	}

}
