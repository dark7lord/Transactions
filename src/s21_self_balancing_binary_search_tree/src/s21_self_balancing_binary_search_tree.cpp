#include "../s21_self_balancing_binary_search_tree.h"

namespace s21 {
using Tree = SelfBalancingBinarySearchTree;

static void copyTree(Node*& destination, const Node* source) {
  if (source == nullptr) {
    destination = nullptr;
    return;
  }

  destination = new Node(source->key, source->value, source->time_limit);
  copyTree(destination->left, source->left);
  copyTree(destination->right, source->right);
}

static void clearTree(Node*& node) {
  if (node == nullptr) return;

  clearTree(node->left);
  clearTree(node->right);
  delete node;
  node = nullptr;
}

const Value* Tree::get(const Key& key) noexcept {
  checkNodesWithTtl_();
  Node* result_node = findNode(root_, key);
  if (result_node) {
    return &(result_node->value);
  } else {
    return nullptr;
  }
}

void Tree::set(const Key& key, const Value& value, TimeLimit ttl) {
  if (ttl == 0) {
    throw KeyValueStorageException("the ttl " + std::to_string(ttl) +
                                   " is not valid");
  }
  checkNodesWithTtl_();
  root_ = insert(root_, key, value, ttl);
}

bool Tree::exists(const Key& key) noexcept {
  checkNodesWithTtl_();
  return findNode(root_, key) != nullptr;
}

bool Tree::del(const Key& key) noexcept {
  checkNodesWithTtl_();

  Node* current_root = findNode(root_, key);
  if (!current_root) return false;
  root_ = deleteNode(root_, key);

  return true;
}

static void updateValue(Value& old_value, const Value& new_value,
                        const Key& key) {
  if (old_value[key] != new_value[key] && new_value[key] != "-") {
    old_value[key] = new_value[key];
  }
}

void Tree::update(const Key& key, const Value& new_value) {
  checkNodesWithTtl_();
  Node* node = findNode(root_, key);

  if (!node) throw IKeyValueStorage::KeyNotExistsException();
  Value& old_value = node->value;

  const auto& fields = {"first_name", "last_name", "birth_year", "city",
                        "coins_number"};

  for (const auto& field_name : fields) {
    updateValue(old_value, new_value, field_name);
  }
}

/***  "some text" == "-" is true, operator "==" is overloaded  ***/
std::vector<Key> Tree::find(const Value& value) noexcept {
  checkNodesWithTtl_();
  std::vector<Key> keys_by_value;

  auto find_keys_by_value = [&value, &keys_by_value](Node* node) {
    if (node->value == value) {
      keys_by_value.push_back(node->key);
    }
  };
  traverseTree(root_, find_keys_by_value);

  return keys_by_value;
}

std::vector<Key> Tree::keys() noexcept {
  checkNodesWithTtl_();
  std::vector<Key> all_keys;

  auto collect_keys = [&all_keys](Node* node) {
    all_keys.push_back(node->key);
  };
  traverseTree(root_, collect_keys);

  return all_keys;
}

void Tree::rename(const Key& old_key, const Key& new_key) {
  checkNodesWithTtl_();
  Node* old_node = findNode(root_, old_key);
  if (!old_node) throw IKeyValueStorage::KeyNotExistsException();

  Node* new_node = findNode(root_, new_key);
  if (new_node) throw IKeyValueStorage::KeyExistsException();

  Value&& value = std::move(old_node->value);
  root_ = deleteNode(root_, old_key);
  root_ = insert(root_, new_key, value);
}

static constexpr TimeLimit NON_EXISTENT = 0;
static constexpr TimeLimit DELETE_TTL = 0;
static constexpr TimeLimit NO_TTL = -1;

TimeLimit Tree::ttl(const Key& key) noexcept {
  checkNodesWithTtl_();
  Node* node = findNode(root_, key);

  if (!node) {
    return NON_EXISTENT;
  }

  int time_limit = node->time_limit;

  if (time_limit < 0) {
    return NO_TTL;
  }
  int time_difference = time_limit - time(0);
  if (time_limit == 0 || time_difference <= 0) {
    deleteNode(root_, key);
    return DELETE_TTL;
  }

  return time_difference;
}

void Tree::checkNodesWithTtl_() {
  for (const auto& node : nodes_with_TTL_) {
    if (ttl(node->key) == (DELETE_TTL)) {
      deleteNode(root_, node->key);
    }
  }
}

std::vector<Value> Tree::showall() noexcept {
  checkNodesWithTtl_();
  std::vector<Value> values;

  auto collect_values = [&values](Node* node) {
    values.push_back(node->value);
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

void Tree::save(const std::string& filename) {
  checkNodesWithTtl_();
  std::ofstream output_file(filename, std::ios::trunc);

  if (output_file.is_open()) {
    int count = 0;

    auto collect_entries = [&output_file, &count](Node* node) {
      output_file << entryToStr(node->key, node->value) << std::endl;
      count += 1;
    };
    traverseTree(root_, collect_entries);

    output_file.close();

  } else {
    throw IKeyValueStorage::CantOpenFile(filename);
  }
}
}  // namespace s21
