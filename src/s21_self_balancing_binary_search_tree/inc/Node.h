#ifndef AVL_NODE
#define AVL_NODE

#include <functional>

#include "../../s21_i_key_value_storage/s21_i_key_value_storage.h"

using std::string;

namespace s21 {
class Node {
 public:
  s21::Key key;
  s21::Value value;
  Node* left;
  Node* right;
  int height;
  s21::TimeLimit time_limit;

  Node(const s21::Key& k, const s21::Value& v, s21::TimeLimit = -1);
  ~Node();
};

Node* insert(Node* node, const Key& key, const Value& value,
             TimeLimit ttl = -1);

Node* balance(Node* node);
Node* findNode(Node* node, Key key);
Node* deleteNode(Node* root, const Key& key);
void traverseTree(Node*, const std::function<void(Node*)>&);
}  // namespace s21

#endif
