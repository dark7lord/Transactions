#include "../inc/Node.h"

#include <iostream>

namespace s21 {
Node::Node(const s21::Key& k, const s21::Value& v, s21::TimeLimit t)
    : key(k),
      value(v),
      left(nullptr),
      right(nullptr),
      height(1),
      time_limit(t) {
  if (time_limit > 0) time_limit = time(0) + t;  // timestamp
}

Node::~Node() {
  delete left;
  delete right;
  left = right = nullptr;
}

static int getHeight(Node* node) {
  return (node != nullptr) ? node->height : 0;
}

static void updateHeight(Node* node) {
  if (!node) return;
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

static Node* rotateLeft(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  y->left = x;
  updateHeight(x);
  updateHeight(y);

  return y;
}

static Node* rotateRight(Node* y) {
  Node* x = y->left;
  y->left = x->right;
  x->right = y;
  updateHeight(y);
  updateHeight(x);

  return x;
}

static bool isLeftHeavy(Node* node) {
  return getHeight(node->left) > getHeight(node->right);
}

static bool isRightHeavy(Node* node) {
  return getHeight(node->right) > getHeight(node->left);
}

Node* balance(Node* node) {
  updateHeight(node);

  int balanceFactor = getHeight(node->left) - getHeight(node->right);
  if (balanceFactor > 1) {
    if (isRightHeavy(node->left)) {
      node->left = rotateLeft(node->left);
    }

    return rotateRight(node);
  } else if (balanceFactor < -1) {
    if (isLeftHeavy(node->right)) {
      node->right = rotateRight(node->right);
    }

    return rotateLeft(node);
  }

  return node;
}

Node* insert(Node* node, const Key& key, const Value& value, TimeLimit ttl) {
  if (node == nullptr) {
    return new Node(key, value, ttl);
  }

  if (key < node->key) {
    node->left = insert(node->left, key, value, ttl);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value, ttl);
  } else {
    throw IKeyValueStorage::KeyExistsException();
  }

  return balance(node);
}

Node* findNode(Node* node, Key key) {
  if (!node) return nullptr;

  if (key == node->key)
    return node;
  else if (key < node->key)
    return findNode(node->left, key);
  else
    return findNode(node->right, key);
}

static Node* minValueNode(Node* node) {
  Node* current = node;

  while (current->left != nullptr) current = current->left;

  return current;
}

Node* deleteNode(Node* root, const Key& key) {
  if (root == nullptr) return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == nullptr) || (root->right == nullptr)) {
      Node* temp = root->left ? root->left : root->right;

      if (temp == nullptr) {
        root = nullptr;
      } else {
        *root = *temp;
      }

      delete (temp);
    } else {
      Node* temp = minValueNode(root->right);
      root->key = temp->key;
      root->value = temp->value;
      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == nullptr) return root;

  return balance(root);
}

void traverseTree(Node* node, const std::function<void(Node*)>& func) {
  if (node != nullptr) {
    traverseTree(node->left, func);
    func(node);
    traverseTree(node->right, func);
  }
}
}  // namespace s21
