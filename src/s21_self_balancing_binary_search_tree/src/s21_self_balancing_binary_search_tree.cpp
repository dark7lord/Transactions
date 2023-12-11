#include "../s21_self_balancing_binary_search_tree.h"

namespace s21 {
	using Tree = SelfBalancingBinarySearchTree;
	using Node = AVL_Node;

	const Value* Tree::get(const Key& key) noexcept {
		check_nodes_with_TTL();
		Node* result_node = find_node(_root, key);
		if (result_node) {
			return &(result_node->value);
		} else {
			return nullptr;
		}
	}

	void Tree::set(const Key& key, const Value& value, TimeLimit ttl) {
		check_nodes_with_TTL();
		_root = insert(_root, key, value, ttl);
	}

	bool Tree::exists(const Key& key) noexcept {
		check_nodes_with_TTL();
		return find_node(_root, key) != nullptr;
	}

	bool Tree::del(const Key& key) noexcept {
		check_nodes_with_TTL();
		Node* current_root = _root;
		_root = delete_node(current_root, key);
		return current_root != _root;
	}

	// Рекурсия, я люблю тебя
	void _print_tree(Node* root, int level = 0) {
		int padding = 3;

		if (root != nullptr) {
			_print_tree(root->right, level + 1);
			std::cout	<< std::string(level * padding, ' ')
						<< root->key
						<< std::endl;
			_print_tree(root->left, level + 1);
		}
	}

	void Tree::print_tree() {
		check_nodes_with_TTL();
		std::cout << "Printing Tree:\n";
		std::cout << "--------------------\n";
		_print_tree(_root);
		std::cout << "--------------------\n";
	}

	// TODO: перегрузить оператор != или = взамен этой функции ниже
	void update_value (Value& old_value, const Value& new_value, const Key& key) {
		if (old_value[key] != new_value[key] && new_value[key] != "-") {
			old_value[key] = new_value[key];
		}
	}

	void Tree::update(const Key& key, const Value& new_value) {
		check_nodes_with_TTL();
		Node* node = find_node(_root, key);

		if (!node) throw IKeyValueStorage::KeyNotExistsException();
		Value& old_value = node -> value;

		const auto& fields = {
			"first_name",
			"last_name",
			"birth_year",
			"city",
			"coins_number"
		};

		for (const auto& field_name : fields) {
			update_value(old_value, new_value, field_name);
		}
	}

	/***  "some text" == "-" is true, operator "==" is overloaded  ***/
	std::vector<Key> Tree::find(const Value& value) noexcept {
		check_nodes_with_TTL();
		std::vector<Key> keys_by_value;

		auto find_keys_by_value = [&value, &keys_by_value](Node* node) {
			if (node->value == value) {
				keys_by_value.push_back(node->key);
			}
		};
		traverse_tree(_root, find_keys_by_value);

		return keys_by_value;
	}

	std::vector<Key> Tree::keys(void) noexcept {
		check_nodes_with_TTL();
		std::vector<Key> all_keys;

		auto collect_keys = [&all_keys](Node* node) {
			all_keys.push_back(node->key);
		};
		traverse_tree(_root, collect_keys);

		return all_keys;
	}

	void Tree::rename(const Key& old_key, const Key& new_key) {
		check_nodes_with_TTL();
		Node* old_node = find_node(_root, old_key);
		if (!old_node) throw IKeyValueStorage::KeyNotExistsException();

		Node* new_node = find_node(_root, new_key);
		if (new_node) throw IKeyValueStorage::KeyExistsException();

		Value&& value = std::move(old_node -> value);
		_root = delete_node(_root, old_key);
		_root = insert(_root, new_key, value);
	}

	constexpr TimeLimit NON_EXISTENT = 0;
	constexpr TimeLimit DELETE_TTL = 0;
	constexpr TimeLimit NO_TTL = -1;

	TimeLimit Tree::ttl(const Key& key) noexcept {
		check_nodes_with_TTL();
		Node *node = find_node(_root, key);

		if (!node) {
			return NON_EXISTENT;
		}

		int time_limit = node -> time_limit;

		if (time_limit < 0) {
			return NO_TTL;
		}
		int time_difference = time_limit - time(0);
		if (time_limit == 0 || time_difference <= 0 ) {
			delete_node(_root, key);
			// del(key);
			return DELETE_TTL;
		}

		return time_difference;
	}

	void Tree::check_nodes_with_TTL() {
		for (const auto& node : _nodes_with_TTL) {
			if (ttl(node -> key) == (DELETE_TTL)) {
				delete_node(_root, node->key);
			}
		}
	}

	std::vector<Value>	Tree::showall() noexcept {
		check_nodes_with_TTL();
		std::vector<Value> values;

		auto collect_values = [&values](Node* node) {
			values.push_back(node -> value);
		};
		traverse_tree(_root, collect_values);

		return values;
	}

	std::string entry_to_str(const Key& key, const Value& value) {
		std::ostringstream oss;
		oss << key << ' '
			<< std::quoted(value.last_name) << ' '
			<< std::quoted(value.first_name) << ' '
			<< value.birth_year << ' '
			<< std::quoted(value.city) << ' '
			<< value.coins_number;

		return oss.str();
	}

	void Tree::save(const std::string& filename) {
		check_nodes_with_TTL();
		std::ofstream output_file(filename);

		if (output_file.is_open()) {
			int count = 0;

			auto collect_entries = [&output_file, &count](Node* node) {
				output_file << entry_to_str(node -> key, node -> value) << std::endl;
				count += 1;
			};
			traverse_tree(_root, collect_entries);

			output_file.close();

		} else {
			throw std::ios_base::failure("Failed to open file: " + filename);
		}
	}
}




