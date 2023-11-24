#include "s21_self_balancing_binary_search_tree.h"

// typedef SelfBalancingBinarySearchTree BinTree;

namespace s21 {

    // SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
    // SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&);
    // SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
    // SelfBalancingBinarySearchTree::~SelfBalancingBinarySearchTree();

    SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree() {}

    void SelfBalancingBinarySearchTree::set(Key k, Value v, TimeLimit t) {
        this -> k = k;
        this -> v = v;
        this -> t = t;
    }

    const Value* SelfBalancingBinarySearchTree::get(Key) const noexcept {
        return &(this -> v);
    }

    // bool SelfBalancingBinarySearchTree::exists(Key) {

    // }

    // void SelfBalancingBinarySearchTree::del(Key) {

    // }

    // std::array<Key> SelfBalancingBinarySearchTree::keys(void) {

    // }

    // void SelfBalancingBinarySearchTree::rename(Key, Key) {

    // }

    // TimeLimit SelfBalancingBinarySearchTree::ttl(Key) {

    // }

    // std::array<Key> SelfBalancingBinarySearchTree::find(Value) {

    // }

    // std::array<Value> SelfBalancingBinarySearchTree::showall(void) {

    // }

    // void SelfBalancingBinarySearchTree::upload(const std::string& filename) {

    // }

    // void SelfBalancingBinarySearchTree::export(const std::string& filename) {

    // }

}
