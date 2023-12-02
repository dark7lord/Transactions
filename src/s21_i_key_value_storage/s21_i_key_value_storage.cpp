#include "s21_i_key_value_storage.h"
// #include <iostream>

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

	bool operator==(const Value& lhs, const Value& rhs) {
		return (
			( lhs.first_name == rhs.first_name		|| rhs.first_name == "-"	) &&
			( lhs.last_name == rhs.last_name		|| rhs.last_name == "-"		) &&
			( lhs.birth_year == rhs.birth_year		|| rhs.birth_year == "-"	) &&
			( lhs.city == rhs.city					|| rhs.city == "-"			) &&
			( lhs.coins_number == rhs.coins_number	|| rhs.coins_number == "-"	)
		);
	}

	std::ostream& operator<<(std::ostream& os, const Value& value) {
		os << "first_name: " << value.first_name << ", "
		<< "last_name: " << value.last_name << ", "
		<< "birth_year: " << value.birth_year << ", "
		<< "city: " << value.city << ", "
		<< "coins_number: " << value.coins_number;
		return os;
	}

}

