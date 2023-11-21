#include <iostream>
#include <string>
// #include "s21_key_value_storage/s21_key_value_storage.h"
#include "s21_hash_table/s21_hash_table.h"


int main() {

    s21::Value v;

    v = {"Ivanov", "Ivan", "2020", "Rostov", "55"};

    s21::HashTable a;
    a.set("Hello, world", v, 5);
    std::cout << a.get("Hello, world").first_name << std::endl;

    // KeyValueStorage<HashTable> a;
    // a.set("Hello, world", "Hello, world", 5);
    // std::cout << a.get("Hello, world") << std::endl;

    // KeyValueStorage<SelfBalancingTree> b;
    // b.set("Hello, world", "Hello, world", 5);
    // std::cout << b.get("Hello, world") << std::endl;
    
};