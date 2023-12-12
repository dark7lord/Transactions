#include <iomanip>
#include <sstream>

#include "../s21_key_value_console_interface.h"

namespace s21 {

const std::string KeyValueConsoleInterface::ARGUMENTS_NUMBER =
    "> ERROR: invalid number of arguments";
const std::string KeyValueConsoleInterface::EMPTY_TOKEN =
    "> ERROR: empty tokens are not expected";

void KeyValueConsoleInterface::tokenize_(
    const std::string& user_input, std::vector<std::string>& out) noexcept {
  std::stringstream ss(user_input);
  std::string token;

  while (ss >> std::quoted(token)) {
    out.push_back(token);
  }
}

bool KeyValueConsoleInterface::validateTokens_(
    const std::vector<std::string>& tokens,
    std::size_t expected_number) noexcept {
  if (tokens.size() != expected_number) {
    std::cout << RED << KeyValueConsoleInterface::ARGUMENTS_NUMBER << NONE
              << std::endl;
    return true;
  }
  for (const std::string& token : tokens) {
    if (token == "") {
      std::cout << RED << KeyValueConsoleInterface::EMPTY_TOKEN << NONE
                << std::endl;
      return true;
    }
  }
  return false;
}

Value KeyValueConsoleInterface::parse_value_dash_(
    const std::string& last_name, const std::string& first_name,
    const std::string& birth_year, const std::string& city,
    const std::string& number_coins) {
  if (!is_non_negative_integer(birth_year) && birth_year != "-") {
    throw std::invalid_argument("unable to cast value \"" + birth_year +
                                "\" to type uint");
  }

  if (!is_non_negative_integer(number_coins) && number_coins != "-") {
    throw std::invalid_argument("unable to cast value \"" + number_coins +
                                "\" to type uint");
  }

  Value value = {last_name, first_name, birth_year, city, number_coins};

  return value;
}

}  // namespace s21