#include "AVL_Node.h"
#include "s21_self_balancing_binary_search_tree.h"

namespace s21 {
	using std::max;
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&);
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
	// SelfBalancingBinarySearchTree::~SelfBalancingBinarySearchTree();

	int SelfBalancingBinarySearchTree::getHeight(AVL_Node* node) {
		return (node != nullptr) ? node->height : 0;
	}

	// Обновление высоты узла
	void SelfBalancingBinarySearchTree::updateHeight(AVL_Node* node) {
		if (node != nullptr) {
			node->height = 1 + max( getHeight(node->left), getHeight(node->right) );
		}
	}

	// Выполнение левого вращения
	// (...) ← _x_  → (yl ← y → (,,,))
	// ==> X swaps places with Y
	// ( (...) ← x → yl ) ← _y_  → (,,,)
	AVL_Node* SelfBalancingBinarySearchTree::rotateLeft(AVL_Node* x) {
		AVL_Node* y = x->right;
		x->right = y->left;
		y->left = x;
		updateHeight(x);
		updateHeight(y);
		std::cout << "	key("<< x -> key << ") going to left" << std::endl;
		std::cout << "	key("<< y -> key << ") going to top" << std::endl;
		return y;
	}

	// Выполнение правого вращения
	// ( ,,, ← x → xr) ←  _y_  →  (...)
	// ==> Y swaps places with X
	// ( ,,, ) ←  _x_  → ( xr ← y → (...))
	AVL_Node* SelfBalancingBinarySearchTree::rotateRight(AVL_Node* y) {
		AVL_Node* x = y->left;
		y->left = x->right;
		x->right = y;
		updateHeight(y);
		updateHeight(x);
		std::cout << "	key("<< y -> key << ") going to right" << std::endl;
		std::cout << "	key("<< x -> key << ") going to top" << std::endl;
		return x;
	}

	// Балансировка узла
	AVL_Node* SelfBalancingBinarySearchTree::balance(AVL_Node* node) {
		updateHeight(node);

		int balanceFactor = getHeight(node->left) - getHeight(node->right);
		if (balanceFactor > 1) {
			if (getHeight(node->left->right) > getHeight(node->left->left)) {
				std::cout << "rotateLeft:" << std::endl;
				node->left = rotateLeft(node->left);
			}
			std::cout << "rotateRight:" << std::endl;
			return rotateRight(node);
		}
		else if (balanceFactor < -1) {
			if (getHeight(node->right->left) > getHeight(node->right->right)) {
				std::cout << "rotateRight:" << std::endl;
				node->right = rotateRight(node->right);
			}
			std::cout << "rotateleft:" << std::endl;
			return rotateLeft(node);
		}

		return node;
	}

	// Вставка узла с рекурсивным обновлением высот и балансировкой
	AVL_Node* SelfBalancingBinarySearchTree::insert(AVL_Node* node, const Key& key, const Value& value) {
		if (node == nullptr) {
			return new AVL_Node(key, value);
		}

		if (key < node->key) {
			std::cout << "trying to insert on the left" << std::endl;
			node->left = insert(node->left, key, value);
		} else if (key > node->key) {
			std::cout << "trying to insert on the right" << std::endl;
			node->right = insert(node->right, key, value);
		} else {
			return node;
			// throw new std::exception
		}

		return balance(node);
	}

	const Value* SelfBalancingBinarySearchTree::get(const Key& key) const noexcept {
		AVL_Node* resultNode = find_node(_root, key);
		if (resultNode) {
			return &(resultNode->value);
		} else {
//			throw std::out_of_range("Key not found"); // or nullptr?
			return nullptr;
		}
	}

	void SelfBalancingBinarySearchTree::set(const Key& key, const Value& value, TimeLimit t) {
		(void) t;
		_root = insert(_root, key, value);
	}

	AVL_Node* SelfBalancingBinarySearchTree::find_node(AVL_Node* node, Key key) const {
		if (!node) {
			return nullptr; // Ключ не найден
		}
		if (key == node->key) {
			return node; // Ключ найден
		} else if (key < node->key) {
			return find_node(node->left, key); // Идем влево
		} else {
			return find_node(node->right, key); // Идем вправо
		}
	}

	bool SelfBalancingBinarySearchTree::exists(const Key& key) const noexcept {
		return find_node(_root, key) != nullptr;
	}

	AVL_Node* SelfBalancingBinarySearchTree::minValueNode(AVL_Node* node) {
		AVL_Node* current = node;

		while (current->left != nullptr)
			current = current->left;

		return current;
	}

	AVL_Node* SelfBalancingBinarySearchTree::deleteNode(AVL_Node* root, Key key) {
		if (root == nullptr) return root;

		if		( key < root->key ) root->left = deleteNode(root->left, key);
		else if	( key > root->key ) root->right = deleteNode(root->right, key);
		else {
			if( (root->left == nullptr) || (root->right == nullptr) ) {

				AVL_Node *temp = root->left ? root->left : root->right;

				if (temp == nullptr) { // No child case
					temp = root;
					root = nullptr;
				}
				else { // One child case
					*root = *temp;
				}

				delete(temp);
			}
			else {
				AVL_Node* temp = minValueNode(root->right);
				root->key = temp->key;
				root->right = deleteNode(root->right, temp->key);
			}
		}

		if (root == nullptr) return root;

		return balance(root);
	}

	bool SelfBalancingBinarySearchTree::del(const Key& key) noexcept {
		AVL_Node* current_root = _root;
		_root = deleteNode(current_root, key);
		return current_root != _root;
	}

	// Рекурсия, я люблю тебя
	void SelfBalancingBinarySearchTree::printTree(AVL_Node* root, int level) {
		if (root != nullptr) {
			printTree(root->right, level + 1);
			for (int i = 0; i < level; i++) {
				std::cout << "   ";
			}
			std::cout << root->key << "\n";
			printTree(root->left, level + 1);
		}
	}

	void SelfBalancingBinarySearchTree::printTree() {
		std::cout << "Printing Tree:\n";
		std::cout << "--------------------\n";
		printTree(_root);
		std::cout << "--------------------\n";
	}

	void update_value (Value& old_value, const Value& new_value, const Key& key) {
		if (old_value[key] != new_value[key] && new_value[key] != "-") {
			old_value[key] = new_value[key];
		}
	}

	void SelfBalancingBinarySearchTree::update(const Key& key, const Value& new_value) {
		AVL_Node* node = find_node(_root, key);

		if (!node) throw std::out_of_range("Key not found");
		Value& old_value = node -> value;

		// (void)new_value;

		// old_value.first_name = new_value
		// (old_value[key] != new_value[key] && new_value[key] != "-") && old_value[key] = new_value[key];
		update_value(old_value, new_value, "first_name");
		update_value(old_value, new_value, "last_name");
		update_value(old_value, new_value, "birth_year");
		update_value(old_value, new_value, "city");
		update_value(old_value, new_value, "coins_number");
	}

	std::vector<Key> SelfBalancingBinarySearchTree::keys(void) const noexcept {
		return std::vector<Key>();
	}
	void SelfBalancingBinarySearchTree::rename(const Key&, const Key&) {}
	TimeLimit SelfBalancingBinarySearchTree::ttl(const Key&) const noexcept {
		return TimeLimit();
	}
	std::vector<Key> SelfBalancingBinarySearchTree::find(const Value&) const noexcept {
		return std::vector<Key>();
	}
//		std::vector<Value> showall(void) const noexcept ; //  согласовать использование итератора
	void SelfBalancingBinarySearchTree::upload(const std::string&) {}
//		void s21::SelfBalancingBinarySearchTree::export(const std::string& filename) const override; // delete 0
	std::size_t SelfBalancingBinarySearchTree::size() const noexcept {
		return 0;
	}
}




