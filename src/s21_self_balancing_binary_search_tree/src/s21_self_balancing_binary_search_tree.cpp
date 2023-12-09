#include "../inc/AVL_Node.h"
#include "../s21_self_balancing_binary_search_tree.h"

namespace s21 {
	using std::max;
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&&);
	// SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree&);
	// SelfBalancingBinarySearchTree::~SelfBalancingBinarySearchTree();

	int SelfBalancingBinarySearchTree::getHeight(AVL_Node* node) const {
		return (node != nullptr) ? node->height : 0;
	}

	// Обновление высоты узла
	void SelfBalancingBinarySearchTree::updateHeight(AVL_Node* node) const {
		if (node != nullptr) {
			node->height = 1 + max( getHeight(node->left), getHeight(node->right) );
		}
	}

	// Выполнение левого вращения
	// (...) ← _x_  → (yl ← y → (,,,))
	// ==> X swaps places with Y
	// ( (...) ← x → yl ) ← _y_  → (,,,)
	AVL_Node* SelfBalancingBinarySearchTree::rotateLeft(AVL_Node* x) const {
		AVL_Node* y = x->right;
		x->right = y->left;
		y->left = x;
		updateHeight(x);
		updateHeight(y);
		// std::cout << "	key("<< x -> key << ") going to left" << std::endl;
		// std::cout << "	key("<< y -> key << ") going to top" << std::endl;
		return y;
	}

	// Выполнение правого вращения
	// ( ,,, ← x → xr) ←  _y_  →  (...)
	// ==> Y swaps places with X
	// ( ,,, ) ←  _x_  → ( xr ← y → (...))
	AVL_Node* SelfBalancingBinarySearchTree::rotateRight(AVL_Node* y) const {
		AVL_Node* x = y->left;
		y->left = x->right;
		x->right = y;
		updateHeight(y);
		updateHeight(x);
		// std::cout << "	key("<< y -> key << ") going to right" << std::endl;
		// std::cout << "	key("<< x -> key << ") going to top" << std::endl;
		return x;
	}

	// Балансировка узла
	AVL_Node* SelfBalancingBinarySearchTree::balance(AVL_Node* node) const {
		updateHeight(node);

		int balanceFactor = getHeight(node->left) - getHeight(node->right);
		if (balanceFactor > 1) {
			if (getHeight(node->left->right) > getHeight(node->left->left)) {
				// std::cout << "rotateLeft:" << std::endl;
				node->left = rotateLeft(node->left);
			}
			// std::cout << "rotateRight:" << std::endl;
			return rotateRight(node);
		}
		else if (balanceFactor < -1) {
			if (getHeight(node->right->left) > getHeight(node->right->right)) {
				// std::cout << "rotateRight:" << std::endl;
				node->right = rotateRight(node->right);
			}
			// std::cout << "rotateleft:" << std::endl;
			return rotateLeft(node);
		}

		return node;
	}

	// Вставка узла с рекурсивным обновлением высот и балансировкой
	AVL_Node* SelfBalancingBinarySearchTree::insert(AVL_Node* node, const Key& key, const Value& value, TimeLimit ttl) {
		if (node == nullptr) {
			return new AVL_Node(key, value, ttl);
		}

		if (key < node->key) {
			node->left = insert(node->left, key, value, ttl);
		} else if (key > node->key) {
			node->right = insert(node->right, key, value, ttl);
		} else {
			// Это вставка уже в существующий ключ
			// return node;
			throw std::out_of_range("The key" + key + "exists");
		}

		return balance(node);
	}

	const Value* SelfBalancingBinarySearchTree::get(const Key& key) const noexcept {
		AVL_Node* resultNode = find_node(_root, key);
		if (resultNode) {
			return &(resultNode->value);
		} else {
			return nullptr;
		}
	}

	void SelfBalancingBinarySearchTree::set(const Key& key, const Value& value, TimeLimit ttl) {
		_root = insert(_root, key, value, ttl);
	}

	AVL_Node* SelfBalancingBinarySearchTree::find_node(AVL_Node* node, Key key) const {
		if (!node)					return nullptr;

		if (key == node->key)		return node;
		else if (key < node->key)	return find_node(node->left, key);
		else						return find_node(node->right, key);
	}

	bool SelfBalancingBinarySearchTree::exists(const Key& key) const noexcept {
		return find_node(_root, key) != nullptr;
	}

	AVL_Node* SelfBalancingBinarySearchTree::minValueNode(AVL_Node* node) const {
		AVL_Node* current = node;

		while (current->left != nullptr)
			current = current->left;

		return current;
	}

	AVL_Node* SelfBalancingBinarySearchTree::deleteNode(AVL_Node* root, const Key& key) const {
		if (root == nullptr) return root;

		if		( key < root->key ) root->left = deleteNode(root->left, key);
		else if	( key > root->key ) root->right = deleteNode(root->right, key);
		else {
			if( (root->left == nullptr) || (root->right == nullptr) ) {

				AVL_Node *temp = root->left ? root->left : root->right;

				if (temp == nullptr) {
					root = nullptr;
				}
				else {
					*root = *temp;
				}

				delete(temp);
			}
			else {
				AVL_Node* temp = minValueNode(root->right);
				root->key = temp->key;
				root->value = temp->value;
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
		int padding = 4;

		if (root != nullptr) {
			printTree(root->right, level + 1);
			std::cout	<< std::string(level * padding, ' ')
						<< root->key
						<< std::endl;
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

		// old_value.first_name = new_value
		// (old_value[key] != new_value[key] && new_value[key] != "-") && old_value[key] = new_value[key];
		update_value(old_value, new_value, "first_name");
		update_value(old_value, new_value, "last_name");
		update_value(old_value, new_value, "birth_year");
		update_value(old_value, new_value, "city");
		update_value(old_value, new_value, "coins_number");
	}

	void find_recursive(AVL_Node *node, std::vector<Key> &arrKeys, const Value &value) {
		if (node != nullptr) {
			find_recursive(node -> left, arrKeys, value);

			if (node -> value == value) arrKeys.push_back(node -> key);

			find_recursive(node -> right, arrKeys, value);
		}
	}

	std::vector<Key> SelfBalancingBinarySearchTree::find(const Value& value) const noexcept {
		std::vector<Key> arrKeys;
		find_recursive(_root, arrKeys, value);

		return arrKeys;
	}

	void find_recursive(AVL_Node *node, std::vector<Key> &arrKeys) {
		if (node != nullptr) {
			find_recursive(node -> left, arrKeys);
			arrKeys.push_back(node -> key);
			find_recursive(node -> right, arrKeys);
		}
	}

	std::vector<Key> SelfBalancingBinarySearchTree::keys(void) const noexcept {
		std::vector<Key> arrKeys;
		find_recursive(_root, arrKeys);

		return arrKeys;
	}

	void SelfBalancingBinarySearchTree::rename(const Key& old_key, const Key& new_key) {

		const Value *old_value = get(old_key);

		if (old_value == nullptr) {
			throw std::out_of_range("Key not found");
		}

		const Value *value_new_key = get(new_key);

		if (value_new_key != nullptr) {
			throw std::out_of_range("the key" + new_key + "exists");
		}

		del(old_key);
		set(new_key, *old_value);
	}

	#define  NON_EXISTENT  0;
	#define DELETE_TTL  0;
	#define NO_TTL -1;

	TimeLimit SelfBalancingBinarySearchTree::ttl(const Key& key) const noexcept {
		AVL_Node *node = find_node(_root, key);

		if (!node) {
			return NON_EXISTENT;
		}

		int time_limit = node -> time_limit;
		int different = time_limit - time(0);

		if (time_limit < 0) {
			// std::cout << "This node " << key << " immortal\n";
			return NO_TTL;
		}
		else if (time_limit == 0 || different <= 0 ) {
			deleteNode(node, key);
			return DELETE_TTL;
		}


		return different;
	}

	void push_value_recursive(AVL_Node *node, std::vector<Value> &values) {
		if (node != nullptr) {
			push_value_recursive(node -> left, values);
			values.push_back(node -> value);
			push_value_recursive(node -> right, values);
		}
	}

	std::vector<Value>	SelfBalancingBinarySearchTree::showall() const noexcept {
		std::vector<Value> values;
		push_value_recursive(_root, values);

		return values;
	}


	std::vector<std::string> tokenize(const std::string& line) {
		std::vector<string>	tokens;
		std::istringstream	iss(line);
		string				token;

		while (iss >> std::quoted(token)) {
			tokens.push_back(token);
		}

		return tokens;
	}

	void SelfBalancingBinarySearchTree::upload(const std::string& filename) {
		std::ifstream input_file(filename);

		if (!input_file.is_open()) {
			throw std::ios_base::failure("Failed to open file: " + filename);
		}

		string line;
		int count = 0;
		std::map<Key, Value> keys_values; // на случай если одна строка не валидна

		while (std::getline(input_file, line)) {
			try {
				Key key;
				Value value = Value::str_to_value(line, &key);
				keys_values.insert({ key, value });
			}
			catch (const std::exception& e) {
				std::string numbered_line = "Failed to parse line " + std::to_string(++count) + ": " + line;
				std::string type_error = e.what();
				std::string error_msg = numbered_line + "\n" + type_error;

				throw std::runtime_error(error_msg);
			}
		}

		// А что если он пустой? отработает и вернет пустую мапу,
		// но если просто перенос строки, то ошибка парсинга
		for (const auto& [key, value]: keys_values ) {
			set(key, value);
		}

	}

	// TODO: можно вынести в метод AVL_Node
	string node_to_str(const AVL_Node* node) {
		const Value& value = node->value;

		std::ostringstream oss;
		oss << node -> key << ' '
			<< std::quoted(value.last_name) << ' '
			<< std::quoted(value.first_name) << ' '
			<< value.birth_year << ' '
			<< std::quoted(value.city) << ' '
			<< value.coins_number;

		return oss.str();
}

	void push_key_value_recursive(AVL_Node *node, std::vector<std::string> &values) {
		if (node != nullptr) {
			push_key_value_recursive(node -> left, values);

			std::string str = node_to_str(node);
			values.push_back(str);

			push_key_value_recursive(node -> right, values);
		}
	}


	void SelfBalancingBinarySearchTree::save(const std::string& filename) const {

		std::vector<std::string> keys_values;
		std::ofstream output_file(filename);

		push_key_value_recursive(_root, keys_values);

		if (output_file.is_open()) {
			int count = 0;
			for (const auto& line : keys_values) {
				output_file << line << std::endl;;
				count++;
			}
			std::cout << "OK " << count << std::endl;

		} else {
			throw std::ios_base::failure("Failed to open file: " + filename);
		}
	}
}




