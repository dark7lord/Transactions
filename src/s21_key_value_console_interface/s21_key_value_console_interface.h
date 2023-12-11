#ifndef S21_KEY_VALUE_CONSOLE_INTERFACE
#define S21_KEY_VALUE_CONSOLE_INTERFACE

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "s21_i_key_value_storage.h"
#include "s21_self_balancing_binary_search_tree.h"
#include "s21_hash_table.h"

namespace s21 {

	const std::string BLUE = "\033[1;36m";
	const std::string GREY = "\033[1;37m";
	const std::string NONE = "\033[0m";
	const std::string RED = "\033[1;31m";

	class KeyValueConsoleInterface {

	public:

		static const std::string ARGUMENTS_NUMBER;
		static const std::string EMPTY_TOKEN;

		static void	start() noexcept;

	private:

		static IKeyValueStorage*	storage_;
		static bool					show_menu_;
		static bool					on_exit_;

		KeyValueConsoleInterface(KeyValueConsoleInterface& other) = delete;
		KeyValueConsoleInterface(KeyValueConsoleInterface&& other) = delete;
		KeyValueConsoleInterface &operator=(KeyValueConsoleInterface& other) = delete;
		KeyValueConsoleInterface &operator=(KeyValueConsoleInterface&& other) = delete;
		~KeyValueConsoleInterface() = delete;

		static void tokenize_(const std::string& user_input, std::vector<std::string>& out) noexcept;
		static bool validateTokens_(const std::vector<std::string>&, std::size_t) noexcept;

		static void menu_(const std::vector<std::string>&) noexcept;
		static void	files_(const std::vector<std::string>&) noexcept;
		static void binaryTree_(const std::vector<std::string>&) noexcept;
		static void hashTable_(const std::vector<std::string>&) noexcept;
		static void	set_(const std::vector<std::string>&) noexcept;
		static void	get_(const std::vector<std::string>&) noexcept;
		static void	exists_(const std::vector<std::string>&) noexcept;
		static void	del_(const std::vector<std::string>&) noexcept;
		static void	update_(const std::vector<std::string>&) noexcept;
		static void	keys_(const std::vector<std::string>&) noexcept;
		static void	rename_(const std::vector<std::string>&) noexcept;
		static void	ttl_(const std::vector<std::string>&) noexcept;
		static void	find_(const std::vector<std::string>&) noexcept;
		static void	showall_(const std::vector<std::string>&) noexcept;
		static void	upload_(const std::vector<std::string>&) noexcept;
		static void	save_(const std::vector<std::string>&) noexcept;
		static void	exit_(const std::vector<std::string>&) noexcept;

		friend void startMenu() noexcept;
		friend void menu() noexcept;
		friend void runStartUserInput(const std::string&) noexcept;
		friend void runUserInput(const std::string&) noexcept;
	};

} // namespace s21

#endif // S21_KEY_VALUE_CONSOLE_INTERFACE
