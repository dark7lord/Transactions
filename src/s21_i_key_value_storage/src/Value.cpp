#include "../s21_i_key_value_storage.h"

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
		os	<< std::quoted(value.last_name)	<< " "
			<< std::quoted(value.first_name) << " "
			<< value.birth_year	            << " "
			<< std::quoted(value.city)		<< " "
			<< value.coins_number;

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

	Value Value::parse_value(
		const std::string& last_name,
		const std::string& first_name,
		const std::string& birth_year,
		const std::string& city,
		const std::string& number_coins
	) {
		if (!is_non_negative_integer(birth_year)) {
			throw std::invalid_argument("unable to cast value \"" + birth_year + "\" to type uint");
		}

		if (!is_non_negative_integer(number_coins)) {
			throw std::invalid_argument("unable to cast value \"" + number_coins + "\" to type uint");
		}

		Value value = {
			last_name,
			first_name,
			birth_year,
			city,
			number_coins
		};

		return value;
	}

} // namespace s21