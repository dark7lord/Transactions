#include "../s21_i_key_value_storage.h"
#include <set>

namespace s21 {

	void IKeyValueStorage::upload(const std::string& filename) {
		std::ifstream input_file(filename);

		if (!input_file.is_open()) {
			throw IKeyValueStorage::CantOpenFile(filename);
		}

		std::string line;
		int count = 0;
		std::set<Key> keys;

		while (std::getline(input_file, line)) {
			try {
				Key key;
				Value value;
				IKeyValueStorage::str_to_value(line, key, value);
				if (keys.count(key) == 0 && get(key) == nullptr) {
					keys.insert(key);
				}
				else {
					throw IKeyValueStorage::KeyExistsException();
				}
			}
			catch (const std::exception& e) {
				std::string numbered_line = "Failed to parse line " +
					std::to_string(++count) + ": " + line;
				std::string type_error = e.what();
				std::string error_msg = numbered_line + "\n" + type_error;

				throw std::runtime_error(error_msg);
			}
		}

		input_file.clear();
		input_file.seekg(0, std::ios::beg);

		while (std::getline(input_file, line)) {
			Key key;
			Value value;
			IKeyValueStorage::str_to_value(line, key, value);
			set(key, value);
		}
	}

	void IKeyValueStorage::
	str_to_value(const std::string& line, std::string& key, Value& value) {
		auto	tokens = split_to_tokens(line);

		if (tokens.size() != 6) {
			throw IKeyValueStorage::KeyValueStorageException("invalid number of arguments");
		}

		key = tokens[0];
		value = Value::parse_value(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
	}

	IKeyValueStorage::KeyValueStorageException::
	KeyValueStorageException(const std::string &arg) : std::runtime_error(arg) {}

	IKeyValueStorage::KeyExistsException::
	KeyExistsException() : IKeyValueStorage::
		KeyValueStorageException("the key already exists") {}

	IKeyValueStorage::KeyNotExistsException::
	KeyNotExistsException() : IKeyValueStorage::
		KeyValueStorageException("the key does not exists") {}

	IKeyValueStorage::CantOpenFile::
	CantOpenFile(const std::string &filename) : IKeyValueStorage::
		KeyValueStorageException("failed to create or open the file: " + filename) {}


} // namespace s21

