#include "../s21_i_key_value_storage.h"
#include <iostream>
#include <regex>

namespace s21 {

	std::string& Value::operator[](const std::string& key) {
		if (key == "first_name")	return first_name;
		if (key == "last_name")		return last_name;
		if (key == "birth_year")	return birth_year;
		if (key == "city")			return city;
		if (key == "coins_number")	return coins_number;

		throw std::out_of_range("Key not found");
	}

	const std::string& Value::operator[](const std::string& key) const {
		if (key == "first_name")	return first_name;
		if (key == "last_name")		return last_name;
		if (key == "birth_year")	return birth_year;
		if (key == "city")			return city;
		if (key == "coins_number")	return coins_number;

		throw std::out_of_range("Key not found");
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
			os << "(nullptr)";
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

	// // работает только латинница если пробовать A-Za-zА-Яа-я (русский не отрабатывает)
	// // поэтому можно сделать допущение что цифры в имени разрешены
	// bool isLettersOnly(const std::string& str) {
	// 	std::regex lettersOnlyRegex("^[\\p{L}'\" ]+$");
	// 	return std::regex_match(str, lettersOnlyRegex);
	// }

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
		const std::string& first_name,
		const std::string& last_name,
		const std::string& birth_year,
		const std::string& city,
		const std::string& number_coins
	) {
		if (!is_non_negative_integer(birth_year)) {
			throw std::invalid_argument("Invalid birth year \"" + birth_year + "\"");
		}

		if (!is_non_negative_integer(number_coins)) {
			throw std::invalid_argument("Invalid coins number \"" + number_coins + "\"");
		}

		// if (!isLettersOnly(first_name)) {
		// 	throw std::invalid_argument("Invalid first name \"" + first_name + "\"");
		// }

		// if (!isLettersOnly(last_name)) {
		// 	throw std::invalid_argument("Invalid last name \"" + last_name + "\"");
		// }

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
	Value Value::str_to_value(const std::string& line, std::string *key) {
		auto	tokens = split_to_tokens(line);
		int		k;

		if (key && tokens.size() != 6) {
			throw std::runtime_error("Parsing with key, it's error");
		}
		else if (!key && tokens.size() != 5) {
			throw std::runtime_error("Parsing without key, it's error");
		}

		// можно ли сделать перебор типа такого?
		// for (const auto& key : {"first_name", "last_name", "birth_year", "city", "number_coins"})
		if (key) {
			k = 1;
			*key = tokens[0];
		} else {
			k = 0;
		}

		const std::string& first_name = tokens[0 + k];
		const std::string& last_name = tokens[1 + k];
		const std::string& birth_year = tokens[2 + k];
		const std::string& city = tokens[3 + k];
		const std::string& number_coins = tokens[4 + k];

		Value value = parse_value(first_name, last_name, birth_year, city, number_coins);

		return value;
	}

	void IKeyValueStorage::upload(const std::string& filename) {
		std::ifstream input_file(filename);

		if (!input_file.is_open()) {
			throw std::ios_base::failure("Failed to open file: " + filename);
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

} // end of namespace s21

