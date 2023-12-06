#include "../s21_hash_table.h"

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

	/*
	Get pointer to Value under certain key. Returns nullptr if key does not exist.
	*/
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

	/*
	 Check the key existing.
	 */
	bool HashTable::exists(const Key& key) const noexcept {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash(hash, (*table_)[index]);

		return check_key_exists(key, hash, (*table_)[index], first);
	}

	/*
	 Deletes key and value from storage. Returns an indicator of success deletion.
	 */
	bool HashTable::del(const Key& key) noexcept {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash(hash, (*table_)[index]);

		if (check_key_exists(key, hash, (*table_)[index], first)) {
			(*table_)[index].erase(first);
			return true;
		}
		return false;
	}

	void HashTable::update(const Key& key, const Value& val) {
		HashCode    hash = hashCode_(key);
		std::size_t index = indexFor_(hash);
		auto		first = first_bigger_or_equal_hash(hash, (*table_)[index]);

		if (check_key_exists(key, hash, (*table_)[index], first)) {
			first -> val = val;
		} else {
			throw HashTable::KeyException("The key does not exist");
		}
	}

	/*
	Returns a vector of the existing keys.
	*/
	std::vector<Key> HashTable::keys() const noexcept {
		std::vector<Key> res;

		for (std::list<Node>& bucket : *table_) {
			for (Node& node : bucket) {
				res.push_back(node.key);
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
		auto		old_first = first_bigger_or_equal_hash(old_hash, (*table_)[old_index]);
		HashCode    new_hash = hashCode_(new_key);
		std::size_t new_index = indexFor_(new_hash);
		auto		new_first = first_bigger_or_equal_hash(new_hash, (*table_)[new_index]);

		if (old_key == new_key) {
			return;
		}
		if (!check_key_exists(old_key, old_hash, (*table_)[old_index], old_first)) {
//			throw HashTable::KeyException("The key does not exist");
			return;
		}
		if (check_key_exists(new_key, new_hash, (*table_)[new_index], new_first)) {
			new_first -> val = old_first -> val;
		} else {
			(*table_)[new_index].insert(new_first, HashTable::Node(*old_first));
		}
		(*table_)[old_index].erase(old_first);
	}

	TimeLimit HashTable::ttl(const Key&) const noexcept {
		return TimeLimit();
	}

	std::vector<Key> HashTable::find(const Value&) const noexcept {
		return std::vector<Key>();
	}

	std::vector<Value> HashTable::showall() const noexcept {
		std::vector<Value> res;

		for (std::list<Node>& bucket : *table_) {
			for (Node& node : bucket) {
				res.push_back(node.val);
			}
		}
		return res;
	}

	void HashTable::upload(const std::string&) {}

	void HashTable::save(const std::string&) const {}

}