#include "../s21_i_key_value_storage.h"
#include <iostream>
#include <regex>
#include <set>

namespace s21 {

	std::string& Value::operator[](const std::string& key) {
		if (key == "first_name")	return first_name;
		if (key == "last_name")		return last_name;
		if (key == "birth_year")	return birth_year;
		if (key == "city")			return city;
		if (key == "coins_number")	return coins_number;

		throw IKeyValueStorage::KeyNotExistsException();
	}

	const std::string& Value::operator[](const std::string& key) const {
		if (key == "first_name")	return first_name;
		if (key == "last_name")		return last_name;
		if (key == "birth_year")	return birth_year;
		if (key == "city")			return city;
		if (key == "coins_number")	return coins_number;

		throw IKeyValueStorage::KeyNotExistsException();
	}

	std::ostream& operator<<(std::ostream& os, const Value& value) {
		os	<< "first_name: "	<< value.first_name	<< ", "
			<< "last_name: "	<< value.last_name	<< ", "
			<< "birth_year: "	<< value.birth_year	<< ", "
			<< "city: "			<< value.city		<< ", "
			<< "coins_number: "	<< value.coins_number;

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Value* value) {
		if (value == nullptr) {
			os << "(null)";
			return os;
		}

		os	<< "first_name: "	<< value -> first_name	<< ", "
			<< "last_name: "	<< value -> last_name	<< ", "
			<< "birth_year: "	<< value -> birth_year	<< ", "
			<< "city: "			<< value -> city		<< ", "
			<< "coins_number: "	<< value -> coins_number;

		return os;
	}

	bool operator==(const Value& l, const Value& r) {
		return (
			(l.last_name == r.last_name || l.last_name == "-" || r.last_name == "-") &&
			(l.first_name == r.first_name || l.first_name == "-" || r.first_name == "-") &&
			(l.birth_year == r.birth_year || l.birth_year == "-" || r.birth_year == "-") &&
			(l.city == r.city || l.city == "-" || r.city == "-") &&
			(l.coins_number == r.coins_number || l.coins_number == "-" || r.coins_number == "-")
		);
	}

	bool is_non_negative_integer(const std::string& s) {
		std::regex non_negative_integer_regex("^\\d+$");
		return std::regex_match(s, non_negative_integer_regex);
	}

	std::vector<std::string> split_to_tokens(const std::string& line) {
		std::vector<std::string>	tokens;
		std::istringstream			iss(line);
		std::string						token;

		while (iss >> std::quoted(token)) {
			tokens.push_back(token);
		}

		return tokens;
	}

	Value Value::parse_value(
		const std::string& last_name,
		const std::string& first_name,
		const std::string& birth_year,
		const std::string& city,
		const std::string& number_coins
	) {
		if (!is_non_negative_integer(birth_year)) {
			throw IKeyValueStorage::KeyValueStorageException(
				"unable to cast value \"" + birth_year + "\" to type uint");
		}

		if (!is_non_negative_integer(number_coins)) {
			throw IKeyValueStorage::KeyValueStorageException(
				"unable to cast value \"" + number_coins + "\" to type uint");
		}

		Value value = {
			first_name,
			last_name,
			birth_year,
			city,
			number_coins
		};

		return value;
	}

	// TODO: написать красивый метод вывода ошибки, которая печатает номер строки, саму ее и причина ошибки
	void IKeyValueStorage::str_to_value(const std::string& line, std::string& key, Value& value) {
		auto	tokens = split_to_tokens(line);

		if (tokens.size() != 6) {
			throw IKeyValueStorage::KeyValueStorageException("invalid number of arguments");
		}

		key = tokens[0];
		value = Value::parse_value(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
	}

	void IKeyValueStorage::upload(const std::string& filename) {
		std::ifstream input_file(filename);

		if (!input_file.is_open()) {
			throw std::ios_base::failure("Failed to open file: " + filename);
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
				std::string numbered_line = "Failed to parse line " + std::to_string(++count) + ": " + line;
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

	IKeyValueStorage::KeyValueStorageException::
	KeyValueStorageException(const std::string &arg) : std::runtime_error(arg) {}

	IKeyValueStorage::KeyExistsException::
	KeyExistsException() : IKeyValueStorage::KeyValueStorageException("the key already exists") {}

	IKeyValueStorage::KeyNotExistsException::
	KeyNotExistsException() : IKeyValueStorage::KeyValueStorageException("the key does not exists") {}

} // end of namespace s21

