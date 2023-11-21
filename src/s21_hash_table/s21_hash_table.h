#ifndef S21_HASH_TABLE
#define S21_HASH_TABLE

#include "../s21_key_value_storage/s21_key_value_storage.h"

namespace s21 {

    class HashTable : IKeyValueStorage {
    public:
        HashTable();
        // HashTable(HashTable&) = default;
        // HashTable(HashTable&&) = default;
        // HashTable(HashTable&) = default;
        // HashTable(HashTable&&) = default;
        // ~HashTable() = default;
        Key k;
        Value v;
        TimeLimit t;
        void set(Key, Value, TimeLimit);
        Value get(Key);
        // bool exists(Key);
        // void del(Key);
        // std::vector<Key> keys(void);
        // void rename(Key, Key);
        // TimeLimit ttl(Key);
        // std::vector<Key> find(Value);
        // std::vector<Value> showall(void);
        // void upload(const std::string& filename);
        // void s21::export(const std::string& filename);
    };
}

#endif
