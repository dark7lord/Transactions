#include "../s21_key_value_console_interface.h"
#include <sstream>
#include <iomanip>

namespace s21 {

	const std::string KeyValueConsoleInterface::ARGUMENTS_NUMBER = "> ERROR: invalid number of arguments";
	const std::string KeyValueConsoleInterface::EMPTY_TOKEN = "> ERROR: empty tokens are not expected";

	void KeyValueConsoleInterface::tokenize_(const std::string& user_input, std::vector<std::string>& out) noexcept {
		std::stringstream	ss(user_input);
		std::string			token;

		while (ss >> std::quoted(token)) {
			out.push_back(token);
		}
	}

	bool KeyValueConsoleInterface::validateTokens_(const std::vector<std::string>& tokens, std::size_t expected_number) noexcept {
		if (tokens.size() != expected_number) {
			std::cout << RED << KeyValueConsoleInterface::ARGUMENTS_NUMBER << ": " << tokens.size() << NONE << std::endl;
			return true;
		}
		for (const std::string& token : tokens) {
			if (token == "") {
				std::cout << RED << KeyValueConsoleInterface::EMPTY_TOKEN << NONE << std::endl;
				return true;
			}
		}
		return false;
	}

} // namespace s21