#ifndef S21_SELF_BALANCING_BINARY_SEARCH_TREE
#define S21_SELF_BALANCING_BINARY_SEARCH_TREE
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"
#include "inc/Node.h"

using std::map;
using std::string;
using std::vector;

namespace s21 {
class SelfBalancingBinarySearchTree : public IKeyValueStorage {
 public:
  SelfBalancingBinarySearchTree() : root_(nullptr) {}
  ~SelfBalancingBinarySearchTree() {
    if (root_) delete root_;
    root_ = nullptr;
  }
  SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree&) = delete;
  SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&) noexcept =
      delete;
  SelfBalancingBinarySearchTree& operator=(
      const SelfBalancingBinarySearchTree&) = delete;
  SelfBalancingBinarySearchTree& operator=(
      SelfBalancingBinarySearchTree&&) noexcept = delete;

  void set(const Key&, const Value&, TimeLimit = -1) override;
  const Value* get(const Key& key) noexcept override;
  bool exists(const Key&) noexcept override;
  bool del(const Key&) noexcept override;
  void update(const Key&, const Value&) override;
  std::vector<Key> find(const Value&) noexcept override;
  std::vector<Key> keys() noexcept override;
  void rename(const Key&, const Key&) override;
  TimeLimit ttl(const Key&) noexcept override;
  std::size_t save(const std::string&) override;
  std::vector<Value> showall() noexcept override;

 private:
  Node* root_;
};

}  // namespace s21

#endif  // S21_SELF_BALANCING_BINARY_SEARCH_TREE
