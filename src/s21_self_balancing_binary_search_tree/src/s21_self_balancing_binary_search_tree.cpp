#include "../s21_self_balancing_binary_search_tree.h"

namespace s21 {
using Tree = SelfBalancingBinarySearchTree;

const Value* Tree::get(const Key& key) noexcept {
  Node* result_node = findNode(root_, key);
  if (result_node) {
    if (result_node->is_expired()) {
      root_ = deleteNode(root_, result_node->key);
      return nullptr;
    }
    return &(result_node->value);
  } else {
    return nullptr;
  }
}

void Tree::set(const Key& key, const Value& value, TimeLimit ttl) {
  if (ttl == 0) {
    return;
  }
  root_ = insert(root_, key, value, ttl);
}

bool Tree::exists(const Key& key) noexcept {
  Node* node = findNode(root_, key);
  if (node != nullptr) {
    if (node->is_expired()) {
      root_ = deleteNode(root_, node->key);
      return false;
    }
    return true;
  }
  return false;
}

bool Tree::del(const Key& key) noexcept {
  Node* node = findNode(root_, key);
  if (node != nullptr) {
    if (node->is_expired()) {
      root_ = deleteNode(root_, node->key);
      return false;
    }
    root_ = deleteNode(root_, node->key);
    return true;
  }
  return false;
}

static void updateValue(Value& old_value, const Value& new_value,
                        const Key& key) {
  if (old_value[key] != new_value[key] && new_value[key] != "-") {
    old_value[key] = new_value[key];
  }
}

void Tree::update(const Key& key, const Value& new_value) {
  Node* node = findNode(root_, key);

  if (!node || node->is_expired()) {
    if (node) {
      root_ = deleteNode(root_, node->key);
    }
    throw IKeyValueStorage::KeyNotExistsException();
  }

  Value& old_value = node->value;
  const auto& fields = {"first_name", "last_name", "birth_year", "city",
                        "coins_number"};
  for (const auto& field_name : fields) {
    updateValue(old_value, new_value, field_name);
  }
}

/***  "some text" == "-" is true, operator "==" is overloaded  ***/
std::vector<Key> Tree::find(const Value& value) noexcept {
  std::vector<Key> keys_by_value;

  auto find_keys_by_value = [&value, &keys_by_value](Node* node) {
    if (node->value == value && !node->is_expired()) {
      keys_by_value.push_back(node->key);
    }
  };
  traverseTree(root_, find_keys_by_value);

  return keys_by_value;
}

std::vector<Key> Tree::keys() noexcept {
  std::vector<Key> all_keys;

  auto collect_keys = [&all_keys](Node* node) {
    if (!node->is_expired()) {
      all_keys.push_back(node->key);
    }
  };
  traverseTree(root_, collect_keys);

  return all_keys;
}

void Tree::rename(const Key& old_key, const Key& new_key) {
  if (old_key == new_key) {
    return;
  }

  Node* old_node = findNode(root_, old_key);

  if (!old_node || old_node->is_expired()) {
    if (old_node) {
      root_ = deleteNode(root_, old_node->key);
    }
    throw IKeyValueStorage::KeyNotExistsException();
  }

  Value& value = old_node->value;
  Node* new_node = findNode(root_, new_key);

  if (!new_node || new_node->is_expired()) {
    if (new_node) {
      root_ = deleteNode(root_, new_key);
    }
    root_ = deleteNode(root_, old_key);
    root_ = insert(root_, new_key, value);
    return;
  }

  throw s21::IKeyValueStorage::KeyExistsException();
}

static constexpr TimeLimit NON_EXISTENT = 0;
static constexpr TimeLimit NO_TTL = -1;

TimeLimit Tree::ttl(const Key& key) noexcept {
  Node* node = findNode(root_, key);

  if (!node) {
    return NON_EXISTENT;
  }
  if (node->time_limit < 0) {
    return NO_TTL;
  }

  int diff = node->time_limit + (long)node->set_time - (long)time(0);
  if (diff <= 0) {
    root_ = deleteNode(root_, key);
    return NON_EXISTENT;
  }
  return diff;
}

std::vector<Value> Tree::showall() noexcept {
  std::vector<Value> values;

  auto collect_values = [&values](Node* node) {
    if (!node->is_expired()) {
      values.push_back(node->value);
    }
  };
  traverseTree(root_, collect_values);

  return values;
}

static std::string entryToStr(const Key& key, const Value& value) {
  std::ostringstream oss;
  oss << std::quoted(key) << ' ' << std::quoted(value.last_name) << ' '
      << std::quoted(value.first_name) << ' ' << value.birth_year << ' '
      << std::quoted(value.city) << ' ' << value.coins_number;

  return oss.str();
}

std::size_t Tree::save(const std::string& filename) {
  std::ofstream output_file(filename, std::ios::trunc);

  if (!output_file.is_open()) {
    throw IKeyValueStorage::CantOpenFile(filename);
  }

  std::size_t count = 0;
  auto collect_entries = [&output_file, &count](Node* node) {
    if (!node->is_expired()) {
      output_file << entryToStr(node->key, node->value) << std::endl;
      count++;
    }
  };
  traverseTree(root_, collect_entries);
  output_file.close();
  return count;
}

}  // namespace s21
