#ifndef S21_SELF_BALANCING_BINARY_SEARCH_TREE
#define S21_SELF_BALANCING_BINARY_SEARCH_TREE
#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"

namespace s21 {

    class SelfBalancingBinarySearchTree : IKeyValueStorage {
    public:
        SelfBalancingBinarySearchTree();
        // SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
        // SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
        // SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&) = default;
        // SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) = default;
        // ~SelfBalancingBinarySearchTree() = default;
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
    };
}

#endif
