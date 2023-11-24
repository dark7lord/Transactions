#include "s21_hash_table.h"

namespace s21 {

    void HashTable::set(Key key, Value val, TimeLimit time) {
        HashCode    hash = this -> hashCode_(key);
        Node*       node = new HashTable::Node({hash, key, val, time});
        std::size_t index = indexFor_(hash);
        std::list<Node>&  bucket = (*table_)[index];

        std::cout << "Set New node - key " << key << std::endl;
        auto place = first_bigger_or_equal_hash(hash, bucket);
        place = check_same_key(key, hash, bucket, place);
        if (place == bucket.end()) {
            bucket.push_front(*node);
        } else {
            if (place -> key == key) {
                throw HashTable::KeyException("The key already exists");
            } else {
                bucket.insert(place, *node);
            }
        }
        currentLoadCount_++;
        if (HashTable::currentLoadFactor_() >= initialLoadFactor_) {
            HashTable::increaseTable_();
        }
            
        std::cout << "Changed list index " << index << std::endl;
        std::cout << "New lst size " << (*table_)[index].size() << std::endl;
    }

    const Value* HashTable::get(Key key) const noexcept {
        HashCode    hash = this -> hashCode_(key);
        std::size_t index = indexFor_(hash);
        auto first = (*table_)[index].begin();
        auto last = (*table_)[index].end();

        while (first != last && first -> hash <= hash) {
            if (hash == first -> hash && key == first -> key) {
                return &(first -> val);
            }
            first++;
        }
        return nullptr;
    }

    /*
    Standart boost realization of hash_code(std::string) function. The 
    irrational golden ratio 0x9e3779b9 is used for generating non-collinear 
    binary sequence.
    */
    HashCode HashTable::hashCode_(Key key) const noexcept {
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
        return 0.5;
    }
    
    void HashTable::increaseTable_() {}

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

    std::list<HashTable::Node>::iterator 
    check_same_key(Key key,
                   const HashCode& hash, 
                   const std::list<HashTable::Node>& lst,
                   std::list<HashTable::Node>::iterator first) noexcept {
        std::cout << "Check suspicious hash - hash " << hash << std::endl;
        auto last = lst.end();

        for (; first != last; first++) {
            if (hash == first -> hash && key == first -> key) {
                return first;
            }
            if (hash > first -> hash) {
                return first;
            }
        }
        return first;
    }

    HashTable::HashTable() {
        std::cout << "Create Hash Table - default constructor" << std::endl;
        currentBucketCount_ = initialBucketCount_;
        table_ = new std::vector<std::list<Node>>(initialBucketCount_);
        table_ -> shrink_to_fit();
    }

    HashTable::HashTable(HashTable& other) {
        std::cout << "Create Hash Table - copy constructor" << std::endl;
        table_ = new std::vector<std::list<Node>>(*other.table_);
    }

    HashTable::HashTable(HashTable&& other) {
        std::cout << "Create Hash Table - move constructor" << std::endl;
        table_ = std::move(other.table_);
    }

    HashTable& HashTable::operator=(HashTable& other) {
        std::cout << "Copy Hash Table - copy operator" << std::endl;
        if (this != &other) {
            table_ = new std::vector<std::list<Node>>(*other.table_);
        }
        return *this;
    }

    HashTable& HashTable::operator=(HashTable&& other) {
        std::cout << "Move Hash Table - move operator" << std::endl;
        if(this != &other) {
            table_ = std::move(other.table_);
        } 
        return *this;
    }

    HashTable::~HashTable() {
        std::cout << "Destroy Hash Table - destructor" << std::endl;
        delete table_;
    }

    HashTable::HashTableException::HashTableException(const std::string &arg)
        : std::runtime_error(arg) {}

    HashTable::KeyException::KeyException(const std::string &arg)
        : HashTable::HashTableException(arg) {}

    // bool HashTable::exists(Key) {

    // }

    // void HashTable::del(Key) {

    // }

    // std::array<Key> HashTable::keys(void) {

    // }

    // void HashTable::rename(Key, Key) {

    // }

    // TimeLimit HashTable::ttl(Key) {

    // }

    // std::array<Key> HashTable::find(Value) {
   
    // }

    // std::array<Value> HashTable::showall(void) {
        
    // }

    // void HashTable::upload(const std::string& filename) {

    // }

    // void HashTable::export(const std::string& filename) {

    // }

}