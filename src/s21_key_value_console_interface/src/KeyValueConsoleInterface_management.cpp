#include <vector>

#include "../s21_key_value_console_interface.h"

using namespace s21;

IKeyValueStorage* KeyValueConsoleInterface::storage_ = nullptr;

void KeyValueConsoleInterface::binaryTree_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 1)) {
    return;
  }
  if (storage_ != nullptr) {
    delete storage_;
  }
  storage_ = new SelfBalancingBinarySearchTree();
}

void KeyValueConsoleInterface::hashTable_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 1)) {
    return;
  }
  if (storage_ != nullptr) {
    delete storage_;
  }
  storage_ = new HashTable();
}

void KeyValueConsoleInterface::set_(
    const std::vector<std::string>& tokens) noexcept {
  TimeLimit time = -1;
  if (!(tokens.size() == 7 || tokens.size() == 9)) {
    std::cout << RED << KeyValueConsoleInterface::ARGUMENTS_NUMBER << NONE
              << std::endl;
    return;
  }
  if (tokens.size() == 9 && tokens[7] != "EX") {
    std::cout << RED << "> ERROR: 'EX' expected on position 7" << NONE
              << std::endl;
    return;
  }
  for (const std::string& token : tokens) {
    if (token == "") {
      std::cout << RED << KeyValueConsoleInterface::EMPTY_TOKEN << NONE
                << std::endl;
      return;
    }
  }
  try {
    if (tokens.size() == 9) {
      time = std::stoi(tokens[8]);
      if (time < 0) {
        std::cout << RED << "> ERROR: time limit should be positive" << NONE
                  << std::endl;
        return;
      }
    }
    storage_->set(tokens[1],
                  Value::parse_value(tokens[2], tokens[3], tokens[4], tokens[5],
                                     tokens[6]),
                  time);
    std::cout << GREY << "> OK" << NONE << std::endl;
  } catch (std::exception& e) {
    std::cout << RED << "> ERROR: " << e.what() << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::get_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  const Value* val = storage_->get(tokens[1]);
  if (val == nullptr) {
    std::cout << GREY << "> (null)" << NONE << std::endl;
  } else {
    std::cout << GREY << "> " << *val << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::exists_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  std::cout << GREY << "> " << std::boolalpha << storage_->exists(tokens[1])
            << NONE << std::endl;
}

void KeyValueConsoleInterface::del_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  std::cout << GREY << "> " << std::boolalpha << storage_->del(tokens[1])
            << NONE << std::endl;
}

void KeyValueConsoleInterface::update_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 7)) {
    return;
  }
  try {
    storage_->update(
        tokens[1], parse_value_dash_(tokens[2], tokens[3], tokens[4], tokens[5],
                                     tokens[6]));
    std::cout << GREY << "> OK" << NONE << std::endl;
  } catch (std::exception& e) {
    std::cout << RED << "> ERROR: " << e.what() << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::keys_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 1)) {
    return;
  }
  std::vector<Key> keys = storage_->keys();
  if (keys.size() == 0) {
    std::cout << GREY << "> Storage is empty" << NONE << std::endl;
  }
  for (std::size_t i = 0; i < keys.size(); i++) {
    std::cout << GREY << i + 1 << ") " << keys[i] << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::rename_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 3)) {
    return;
  }
  try {
    storage_->rename(tokens[1], tokens[2]);
    std::cout << GREY << "> OK" << NONE << std::endl;
  } catch (std::exception& e) {
    std::cout << RED << "> ERROR: " << e.what() << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::ttl_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  TimeLimit tl = storage_->ttl(tokens[1]);
  if (tl > 0) {
    std::cout << GREY << "> " << tl << NONE << std::endl;
  } else {
    std::cout << GREY << "> (null)" << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::find_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 6)) {
    return;
  }
  std::vector<Key> keys =
      storage_->find({tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]});
  if (keys.size() == 0) {
    std::cout << GREY << "> No matches found" << NONE << std::endl;
    return;
  }
  for (std::size_t i = 0; i < keys.size(); i++) {
    std::cout << GREY << i + 1 << ") " << keys[i] << NONE << std::endl;
  }
}

static void print_centered(const string& str, std::size_t width, char delim) {
  std::size_t sp = width - str.size();
  printf(" %*s%s%*s %c", int(sp / 2), "", str.c_str(),
         int(sp / 2) + int(sp % 2), "", delim);
}

void KeyValueConsoleInterface::showall_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 1)) {
    return;
  }

  std::vector<Value> vals = storage_->showall();
  if (vals.size() == 0) {
    std::cout << GREY << "> Storage is empty" << NONE << std::endl;
    return;
  }

  std::vector<std::string> numbers;
  for (std::size_t i = 1; i <= vals.size(); i++) {
    numbers.push_back(std::to_string(i));
  }

  std::size_t number_max_length = (numbers[numbers.size() - 1]).size();
  std::size_t last_name_max_length = std::string("Last name").size();
  std::size_t first_name_max_length = std::string("First name").size();
  std::size_t birth_year_max_length = std::string("Year").size();
  std::size_t city_max_length = std::string("City").size();
  std::size_t coins_number_max_length = std::string("Number of coins").size();

  for (const Value& val : vals) {
    if (get_quoted(val.last_name).size() > last_name_max_length)
      last_name_max_length = get_quoted(val.last_name).size();
    if (get_quoted(val.first_name).size() > first_name_max_length)
      first_name_max_length = get_quoted(val.first_name).size();
    if (val.birth_year.size() > birth_year_max_length)
      birth_year_max_length = val.birth_year.size();
    if (get_quoted(val.city).size() > city_max_length)
      city_max_length = get_quoted(val.city).size();
    if (val.coins_number.size() > coins_number_max_length)
      coins_number_max_length = val.coins_number.size();
  }

  std::cout << GREY << ">";
  print_centered("№", number_max_length + 2, '|');
  print_centered("Last name", last_name_max_length, '|');
  print_centered("First name", first_name_max_length, '|');
  print_centered("Year", birth_year_max_length, '|');
  print_centered("City", city_max_length, '|');
  print_centered("Number of coins", coins_number_max_length, '|');
  std::cout << NONE << std::endl;

  for (std::size_t i = 0; i < vals.size(); i++) {
    std::cout << GREY << ">";
    print_centered(numbers[i], number_max_length, ' ');
    print_centered(get_quoted(vals[i].last_name), last_name_max_length, ' ');
    print_centered(get_quoted(vals[i].first_name), first_name_max_length, ' ');
    print_centered(vals[i].birth_year, birth_year_max_length, ' ');
    print_centered(get_quoted(vals[i].city), city_max_length, ' ');
    print_centered(vals[i].coins_number, coins_number_max_length, ' ');
    std::cout << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::upload_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  try {
    std::size_t res = storage_->upload(tokens[1]);
    std::cout << GREY << "> OK " << res << NONE << std::endl;
  } catch (std::exception& e) {
    std::cout << RED << "> ERROR: " << e.what() << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::save_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 2)) {
    return;
  }
  if (tokens[1].size() < 5 ||
      (tokens[1].substr(tokens[1].size() - 4, 5) != ".dat" &&
       tokens[1].substr(tokens[1].size() - 4, 5) != ".DAT")) {
    std::cout << RED
              << "> ERROR: .dat file_for_test.dat with no empty name expected"
              << NONE << std::endl;
    return;
  }
  try {
    std::size_t res = storage_->save(tokens[1]);
    std::cout << GREY << "> OK " << res << NONE << std::endl;
  } catch (std::exception& e) {
    std::cout << RED << "> ERROR: " << e.what() << NONE << std::endl;
  }
}

void KeyValueConsoleInterface::exit_(
    const std::vector<std::string>& tokens) noexcept {
  if (validateTokens_(tokens, 1)) {
    return;
  }
  delete storage_;
  std::cout << GREY << "GOODBYE!" << NONE << std::endl;
  on_exit_ = true;
}
