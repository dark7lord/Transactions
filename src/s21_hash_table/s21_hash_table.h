#ifndef S21_HASH_TABLE
#define S21_HASH_TABLE

#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"
#include <list>
#include <iostream>

namespace s21 {

    typedef std::size_t HashCode;

    class HashTable : IKeyValueStorage {
    public:

        HashTable();
        HashTable(HashTable&);
        HashTable(HashTable&&);
        HashTable& operator=(HashTable&);
        HashTable& operator=(HashTable&&);
        ~HashTable();

        Key k;
        Value v;
        TimeLimit t;
    
        void set(Key, Value, TimeLimit);
        const Value* get(Key) const noexcept;
        // bool exists(Key);
        // void del(Key);
        // std::vector<Key> keys(void);
        // void rename(Key, Key);
        // TimeLimit ttl(Key);
        // std::vector<Key> find(Value);
        // std::vector<Value> showall(void);
        // void upload(const std::string& filename);
        // void s21::export(const std::string& filename);

        struct HashTableException : std::runtime_error {
            explicit HashTableException(const std::string &arg);
        };

        struct KeyException : HashTableException {
            explicit KeyException(const std::string &arg = "Key not found.");
        };

    private:

        static constexpr std::size_t    initialBucketCount_ = 4;
        static constexpr std::size_t    maximumCapacity_ = 1 << 30;
        static constexpr double         initialLoadFactor_ = 0.75f;
        static constexpr HashCode       hashSeed_ = 4;

        struct Node {
            HashCode    hash;
            Key         key;
            Value       val;
            TimeLimit   time;
        };

        std::vector<std::list<Node>>*   table_;
        std::size_t                     currentBucketCount_;
        std::size_t                     currentLoadCount_;

        HashCode    hashCode_(Key) const noexcept;
        HashCode    indexFor_(HashCode) const noexcept;
        double      currentLoadFactor_() const noexcept;
        void        increaseTable_();

        friend std::list<Node>::iterator 
        first_bigger_or_equal_hash(const HashCode& hash, 
                                   std::list<Node>& lst) noexcept;

        friend std::list<Node>::iterator 
        check_same_key(Key key,
                       const HashCode& hash, 
                       const std::list<Node>& lst,
                       std::list<Node>::iterator first) noexcept ;
        
    };
}

#endif
