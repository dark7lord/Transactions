#include "../s21_i_key_value_storage.h"
#include <map>

namespace s21 {

	void IKeyValueStorage::upload(const std::string& filename) {
		std::ifstream input_file(filename, std::ios::in);

		if (!input_file.is_open()) {
			throw IKeyValueStorage::CantOpenFile(filename);
		}

		std::string line;
		int count = 0;
		// на случай, если одна строка не валидна, всё пишется в мапе, и хранилище не нужно ощищать
		std::map<Key, Value> keys_values;

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

		input_file.close();

		// А что если он пустой? отработает и вернет пустую мапу,
		// но если просто перенос строки, то ошибка парсинга
		for (const auto& [key, value]: keys_values ) {
			// std::cout << key << value << std::endl;
			set(key, value);
		}
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

