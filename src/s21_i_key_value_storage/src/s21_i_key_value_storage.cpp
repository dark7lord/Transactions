#include "../s21_i_key_value_storage.h"
#include <iostream>

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
		os << "first_name: " << value.first_name << ", "
		<< "last_name: " << value.last_name << ", "
		<< "birth_year: " << value.birth_year << ", "
		<< "city: " << value.city << ", "
		<< "coins_number: " << value.coins_number;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Value* value) {
		os << "first_name: " << value -> first_name << ", "
		<< "last_name: " << value -> last_name << ", "
		<< "birth_year: " << value -> birth_year << ", "
		<< "city: " << value -> city << ", "
		<< "coins_number: " << value -> coins_number;
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

} // end of namespace s21

