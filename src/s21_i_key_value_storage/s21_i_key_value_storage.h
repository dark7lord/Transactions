#ifndef S21_KEY_VALUE_STORAGE
#define S21_KEY_VALUE_STORAGE

#include <string>
#include <stdbool.h>
#include <vector>
#include "stdio.h"
#include <sstream>
#include <iomanip>
#include <fstream>

namespace s21 {

	struct Value {
		// Value(); //TODO delete
		// Value(Value&) = default;
		// Value(Value&&) = default;
		// Value& operator=(Value&) = default;
		// Value& operator=(Value&&) = default;
		// ~Value() = default;
		// explicit Value(std::string); // парсер // except

		std::string	last_name; // только буквы или одно -
		std::string	first_name; // только буквы или одно -
		std::string	birth_year; // только 4 цифры или одно -
		std::string	city; // только буквы или одно -
		std::string	coins_number; // любые цифры или одно -

		std::string& operator[](const std::string& key);
		const std::string& operator[](const std::string& key) const;

		static Value parse_value(
			const std::string& first_name,
			const std::string& last_name,
			const std::string& birth_year,
			const std::string& city,
			const std::string& coins_number
		);
	};

	bool operator==(const Value&, const Value&); // return true if one of the values is -

	std::ostream& operator<<(std::ostream& os, const Value& value);
	std::ostream& operator<<(std::ostream& os, const Value* value);

	using Key = std::string;
	using TimeLimit = int;

	class IKeyValueStorage {
	public:
		virtual void				set(const Key&, const Value&, TimeLimit = -1) = 0;
		virtual const Value*		get(const Key&) noexcept = 0;
		virtual bool				exists(const Key&) noexcept = 0;
		virtual bool				del(const Key&) noexcept = 0;
		virtual void				update(const Key&, const Value&) = 0;
		virtual std::vector<Key>	keys() noexcept = 0;
		virtual void				rename(const Key&, const Key&) = 0;
		virtual TimeLimit			ttl(const Key&) noexcept = 0;
		virtual std::vector<Key>	find(const Value&) noexcept = 0;
		virtual std::vector<Value>	showall() noexcept = 0;
		virtual void				upload(const std::string&);
		virtual void				save(const std::string&) = 0;

		virtual ~IKeyValueStorage() = default;

		static void str_to_value(const std::string& line, std::string& key, Value& value);

		struct KeyValueStorageException : std::runtime_error {
			explicit KeyValueStorageException(const std::string &arg);
		};

		struct KeyExistsException : KeyValueStorageException {
			explicit KeyExistsException();
		};

		struct KeyNotExistsException : KeyValueStorageException {
			explicit KeyNotExistsException();
		};
	};

} // namespace s21

#endif // S21_KEY_VALUE_STORAGE
