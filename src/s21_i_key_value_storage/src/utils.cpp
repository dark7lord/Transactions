#include "../s21_i_key_value_storage.h"
#include <regex>
#include <sstream>

namespace s21 {

	std::string get_quoted(const std::string& in) {
		std::stringstream ss;

		ss << std::quoted(in);
		return ss.str();
	}

	std::vector<std::string> split_to_tokens(const std::string& line) {
		std::vector<std::string>	tokens;
		std::istringstream			iss(line);
		std::string					token;

		while (iss >> std::quoted(token)) {
			tokens.push_back(token);
		}

		return tokens;
	}

	bool is_non_negative_integer(const std::string& s) {
		std::regex non_negative_integer_regex("^\\d+$");
		return std::regex_match(s, non_negative_integer_regex);
	}

}