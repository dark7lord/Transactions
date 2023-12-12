#include "../s21_key_value_console_interface.h"
#include <stdlib.h>
#include <unistd.h>
#include <csignal>

static const std::string WELCOME_MESSAGE = ""
	 "Hello! You're lucky, because it is THE BEST CONSOLE INTERFACE EVER!\n"
	 "-------------------------------------------------------------------";

static const std::string START_MENU_MESSAGE = "\n"
	"Now you have the next opportunities:\n"
	"	HASHTABLE (HT): choose the fresh  hashtable to use in next actions.\n"
	"	BINARYTREE (BT): choose the fresh binary tree to use in next actions.\n"
	"	EXIT: exit program.\n\n"
	"You need to choose one and type the command:";

static const std::string MENU_MESSAGE = "\n"
	"Now you have the next opportunities:\n"
	"	HASHTABLE (HT): choose the fresh hashtable to use in next actions.\n"
	"	BINARYTREE (BT): choose the fresh binary tree to use in next actions.\n"
	"	FILES: show the list of available files with with saved storages.\n"
	"	UPLOAD <filename>: load the storage from a .dat file.\n"
	"	SHOWALL: get all records that are in the key-value storage at the moment.\n"
	"	SET <key> <last name> <first name> <year of birth> <city>\n"
	"		<number of current coins> EX <time in seconds>:\n"
	"		set the key and its value.\n"
	"	GET <key>: get the value associated with the key.\n"
	"	EXISTS <key>: check if a record with the given key exists.\n"
	"	DEL <key>: delete the key and the corresponding value (returns true on\n"
	"		success).\n"
	"	EXPORT <filename>: save the storage as a .dat file.\n"
	"	UPDATE <key> <last name> <first name> <year of birth> <city>\n"
	"		<number of current coins>:\n"
	"		updates the value by the corresponding key if such a key exists. If\n"
	"		there is a field that is not planned to change, it is replaced by a\n"
	"		dash '-'.\n"
	"	KEYS: return all the keys that are in the storage.\n"
	"	RENAME <old_key> <new_key>: rename keys.\n"
	"	TTL <key>: view the remaining time to timelimit.\n"
	"	FIND <last name> <first name> <year of birth> <city>\n"
	"		<number of current coins>:\n"
	"		restore the key (or keys) according to a given value. f any fields will\n"
	"		not be searched, it is replaced by a dash '-'.\n"
	"		to restore the key (or keys) according to a given value.\n"
	"	MENU: show this message.\n"
	"	EXIT: exit program.\n\n"
	"You need to choose one and type the command or MENU to see menu:";

static void runArrows() noexcept;

namespace s21 {

	bool KeyValueConsoleInterface::on_exit_ = false;
	bool KeyValueConsoleInterface::show_menu_ = true;

	void startMenu() noexcept;
	void menu() noexcept;
	void runStartUserInput(const std::string&) noexcept;
	void runUserInput(const std::string&) noexcept;

	void KeyValueConsoleInterface::start() noexcept {
		system("clear");
//		std::signal(SI);
		std::cout << BLUE << WELCOME_MESSAGE << NONE << std::endl;
		runArrows();
		while (!std::cin.eof() && !KeyValueConsoleInterface::storage_ && !KeyValueConsoleInterface::on_exit_) {
			startMenu();
		}
		while (!std::cin.eof() && !KeyValueConsoleInterface::on_exit_) {
			menu();
		}
	}

	void KeyValueConsoleInterface::menu_(const std::vector<std::string>& tokens) noexcept {
		if (validateTokens_(tokens, 1)) {
			return;
		}
		std::cout << BLUE << MENU_MESSAGE << NONE << std::endl;
	}

	void KeyValueConsoleInterface::files_(const std::vector<std::string>& tokens) noexcept {
		if (validateTokens_(tokens, 1)) {
			return;
		}
		std::cout << GREY << "Next files are available in current directory:"
			<< NONE << std::endl;
		std::cout << GREY << std::flush;
		std::system("find . -name \"*.dat\"");
		std::cout << NONE << std::flush;
	}

	void startMenu() noexcept {
		std::cout << BLUE << START_MENU_MESSAGE << NONE << std::endl;
		std::string user_input;
		std::getline(std::cin, user_input);
		runStartUserInput(user_input);
	}

	void menu() noexcept {
		if (KeyValueConsoleInterface::show_menu_) {
			std::cout << BLUE << MENU_MESSAGE << NONE << std::endl;
		}
		KeyValueConsoleInterface::show_menu_ = false;
		std::string user_input;
		std::getline(std::cin, user_input);
		runUserInput(user_input);
	}

	void runStartUserInput(const std::string& user_input) noexcept {
		std::vector<std::string> tokens;

		runArrows();
		KeyValueConsoleInterface::tokenize_(user_input, tokens);
		if (tokens.size() == 0) {
			return;
		}
		if (tokens[0] == "HASHTABLE" || tokens[0] == "HT") {
			return KeyValueConsoleInterface::hashTable_(tokens);
		}
		if (tokens[0] == "BINARYTREE" || tokens[0] == "BT") {
			return KeyValueConsoleInterface::binaryTree_(tokens);
		}
		if (tokens[0] == "EXIT") {
			return KeyValueConsoleInterface::exit_(tokens);
		}
		if (tokens[0] == "GOPAL") {
			std::cout << GREY << "I am Groot!" << NONE << std::endl;
			return;
		}
		if (tokens[0] == "DEDELMIR") {
			std::cout << GREY << "Drink a cup of tea. Right now!" << NONE << std::endl;
			return;
		}
		std::cout << RED << "> ERROR: command " << tokens[0] <<
			" is not defined" << NONE << std::endl;
	}

	void runUserInput(const std::string& user_input) noexcept {
		std::vector<std::string> tokens;

		runArrows();
		KeyValueConsoleInterface::tokenize_(user_input, tokens);
		if (tokens.size() == 0) {
			return;
		}
		if (tokens[0] == "HASHTABLE" || tokens[0] == "HT") {
			return KeyValueConsoleInterface::hashTable_(tokens);
		}
		if (tokens[0] == "BINARYTREE" || tokens[0] == "BT") {
			return KeyValueConsoleInterface::binaryTree_(tokens);
		}
		if (tokens[0] == "FILES") {
			return KeyValueConsoleInterface::files_(tokens);
		}
		if (tokens[0] == "UPLOAD") {
			return KeyValueConsoleInterface::upload_(tokens);
		}
		if (tokens[0] == "SHOWALL") {
			return KeyValueConsoleInterface::showall_(tokens);
		}
		if (tokens[0] == "SET") {
			return KeyValueConsoleInterface::set_(tokens);
		}
		if (tokens[0] == "GET") {
			return KeyValueConsoleInterface::get_(tokens);
		}
		if (tokens[0] == "EXISTS") {
			return KeyValueConsoleInterface::exists_(tokens);
		}
		if (tokens[0] == "DEL") {
			return KeyValueConsoleInterface::del_(tokens);
		}
		if (tokens[0] == "EXPORT") {
			return KeyValueConsoleInterface::save_(tokens);
		}
		if (tokens[0] == "UPDATE") {
			return KeyValueConsoleInterface::update_(tokens);
		}
		if (tokens[0] == "KEYS") {
			return KeyValueConsoleInterface::keys_(tokens);
		}
		if (tokens[0] == "RENAME") {
			return KeyValueConsoleInterface::rename_(tokens);
		}
		if (tokens[0] == "TTL") {
			return KeyValueConsoleInterface::ttl_(tokens);
		}
		if (tokens[0] == "FIND") {
			return KeyValueConsoleInterface::find_(tokens);
		}
		if (tokens[0] == "MENU") {
			return KeyValueConsoleInterface::menu_(tokens);
		}
		if (tokens[0] == "EXIT") {
			return KeyValueConsoleInterface::exit_(tokens);
		}
		std::cout << RED << "> ERROR: command " << tokens[0] <<
			" is not defined. Type MENU to see help" << NONE << std::endl;
	}

} // namespace s21

using namespace s21;

static void runArrows() noexcept {
	for (int i = 0; i < 60; ++i) {
		std::cout << BLUE << std::flush;
		for (int j = 0; j < i; ++j)
			write(0, " ", 1);
		write(0, "> > > >", 7);
		for (int j = 0; j < 60 - i; ++j)
			write(0, " ", 1);
		usleep(10000);
		write(0, "\r", 1);
	}
	for (int j = 0; j < 67; ++j)
		write(0, " ", 1);
	write(0, "\r", 1);
	std::cout << NONE << std::flush;
}
