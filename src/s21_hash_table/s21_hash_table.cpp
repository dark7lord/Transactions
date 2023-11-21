#include "s21_hash_table.h"

namespace s21 {

    // HashTable::HashTable(HashTable&);
    // HashTable::HashTable(HashTable&&);
    // HashTable::HashTable(HashTable&);
    // HashTable::HashTable(HashTable&&);
    // HashTable::~HashTable();

    HashTable::HashTable() {}

    void HashTable::set(Key k, Value v, TimeLimit t) {
        this -> k = k;
        this -> v = v;
        this -> t = t;
    }

    Value HashTable::get(Key) {
        return this -> v;
    }

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