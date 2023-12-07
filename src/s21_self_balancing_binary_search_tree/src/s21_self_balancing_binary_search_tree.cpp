#include "../inc/AVL_Node.h"
#include "../s21_self_balancing_binary_search_tree.h"

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
		// std::cout << "	key("<< x -> key << ") going to left" << std::endl;
		// std::cout << "	key("<< y -> key << ") going to top" << std::endl;
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
		// std::cout << "	key("<< y -> key << ") going to right" << std::endl;
		// std::cout << "	key("<< x -> key << ") going to top" << std::endl;
		return x;
	}

	// Балансировка узла
	AVL_Node* SelfBalancingBinarySearchTree::balance(AVL_Node* node) {
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
	AVL_Node* SelfBalancingBinarySearchTree::insert(AVL_Node* node, const Key& key, const Value& value) {
		if (node == nullptr) {
			return new AVL_Node(key, value);
		}

		if (key < node->key) {
			node->left = insert(node->left, key, value);
		} else if (key > node->key) {
			node->right = insert(node->right, key, value);
		} else {
			// Это вставка уже в существующий ключ
			return node;
			// throw new Exception;
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

	void SelfBalancingBinarySearchTree::set(const Key& key, const Value& value, TimeLimit t) {
		(void) t;
		_root = insert(_root, key, value);
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
		const Value *value = get(old_key);

		if (value == nullptr) {
			throw std::out_of_range("Key not found");
		}

		del(old_key);
		set(new_key, *value);
	}


	TimeLimit SelfBalancingBinarySearchTree::ttl(const Key&) const noexcept {
		// AVL_Node* node = find_node(_root, key);

		// if (!node) {
		// 	throw std::out_of_range("Key not found");
		// // 	// return nullptr;
		// }

		// return node -> time_limit;
		return TimeLimit();
	}

	void push_value_recursive(AVL_Node *node, std::vector<Value> &values) {
		if (node != nullptr) {
			push_value_recursive(node -> left, values);
			values.push_back(node -> value);
			push_value_recursive(node -> right, values);
		}
	}


	// void print_values(const std::vector<Value>& values) {
	// 	const int padding = 2;

	// 	int max_index_width = 1;
	// 	int max_last_name_width = 0;
	// 	int max_first_name_width = 0;
	// 	int max_birth_year_width = 4;  // Исходно установим для года
	// 	int max_city_width = 0;
	// 	int max_coins_number_width = 18;  // Исходно установим для количества коинов

	// 	int i = 1;
	// 	for (const auto& value : values) {
	// 		max_index_width = std::max(max_index_width, static_cast<int>(std::to_string(i++).length()));
	// 		max_last_name_width = std::max(max_last_name_width, static_cast<int>(value.last_name.length()));
	// 		max_first_name_width = std::max(max_first_name_width, static_cast<int>(value.first_name.length()));
	// 		max_birth_year_width = std::max(max_birth_year_width, static_cast<int>(value.birth_year.length()));
	// 		max_city_width = std::max(max_city_width, static_cast<int>(value.city.length()));
	// 		max_coins_number_width = std::max(max_coins_number_width, static_cast<int>(value.coins_number.length()));
	// 	}

	// 	std::cout
	// 		<< std::left
	// 		<< std::setw(max_index_width + padding)			<< "№"
	// 		<< std::setw(max_last_name_width + padding + 2)		<< "Last name"
	// 		<< std::setw(max_first_name_width + padding + 2)	<< "First name"
	// 		<< std::setw(max_birth_year_width + padding)	<< "Year"
	// 		<< std::setw(max_city_width + padding + 2)			<< "City"
	// 		<< std::setw(max_coins_number_width + padding)	<< "Number of coins"
	// 		<< std::endl;

	// 	int count = 1;
	// 	for (const auto& value : values) {
	// 		std::cout

	// 			<< std::left << std::setw(max_index_width + padding)			<< count++
	// 			<< std::setw(max_last_name_width + padding + 2)		<< "\"" + value.last_name + "\""
	// 			<< std::setw(max_first_name_width + padding + 2)	<< "\"" + value.first_name + "\""
	// 			<< std::setw(max_birth_year_width + padding)	<< value.birth_year
	// 			<< std::setw(max_city_width + padding + 2)			<< "\"" + value.city + "\""
	// 			 << std::setw(max_coins_number_width + padding)	<< value.coins_number
	// 			<< std::endl;
	// 	}
	// }

	std::vector<Value>	SelfBalancingBinarySearchTree::showall() const noexcept {
	// std::vector<Value> SelfBalancingBinarySearchTree::showall() const noexcept {
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

		if (!input_file) {
			std::cerr
				<< "Error: " << filename
				<< "could not be opened for reading!" << std::endl;
		}

		string line;
		int count = 0;

		while (std::getline(input_file, line)) {
			std::vector<string> tokens = tokenize(line);
			count++;

			if (tokens.size() == 6) {
				Value value {
					tokens[1],
					tokens[2],
					tokens[3],
					tokens[4],
					tokens[5]
				};

				// auto [ key, last_name, first_name, birth_year, city, coins_number ] = tokens;

				std::cout	<< "Key: "			<< tokens[0] << ", "
							<< "Last Name: "	<< value.last_name << ", "
							<< "First Name: "	<< value.first_name << ", "
							<< "Birth Year: "	<< value.birth_year << ", "
							<< "City: "			<< value.city << ", "
							<< "Coins Number: "	<< value.coins_number
							<< std::endl;
			} else {
				std::cerr << "Failed to parse line " << count << " : " << line << std::endl;
				// throw error_reading
			}
			// Here will Value(std::string&)
		}
	}

	string extract_str_node(const AVL_Node* node) {
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

			std::string str = extract_str_node(node);
			values.push_back(str);

			push_key_value_recursive(node -> right, values);
		}
	}


//	void s21::SelfBalancingBinarySearchTree::    export(const std::string& filename) const override; // delete 0
	// void SelfBalancingBinarySearchTree::s21_export(const std::string& filename) const {
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
			std::cerr << "Unable to open file: " << filename << std::endl;
		}

		// for (auto str : keys_values) {
		// 	std::cout << str << std::endl;
		// }
	}
	// std::size_t SelfBalancingBinarySearchTree::size() const noexcept {
	// 	return 0;

	// }

	// std::vector<Value> SelfBalancingBinarySearchTree::showall() const noexcept {
	// 	return  std::vector<Value>();
	// }

	// void SelfBalancingBinarySearchTree::upload(const std::string&) {}

	// void SelfBalancingBinarySearchTree::save(const std::string&) const {}
}




