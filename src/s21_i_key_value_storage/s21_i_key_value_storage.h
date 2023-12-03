#ifndef KEY_VALUE_STORAGE
#define KEY_VALUE_STORAGE

#include <string>
#include <stdbool.h>
#include <vector>

namespace s21 {

	struct Value {
		// Value(); //TODO delete
		// Value(Value&) = default;
		// Value(Value&&) = default;
		// Value& operator=(Value&) = default;
		// Value& operator=(Value&&) = default;
		// ~Value() = default;
		// explicit Value(std::string); // парсер

		std::string	last_name; // только буквы или одно -
		std::string	first_name; // только буквы или одно -
		std::string	birth_year; // только 4 цифры или одно -
		std::string	city; // только буквы или одно -
		std::string	coins_number; // любые цифры или одно -

		std::string& operator[](const std::string& key);
		const std::string& operator[](const std::string& key) const;
	};

	bool operator==(const Value&, const Value&); // return true if one of the values is -

	std::ostream& operator<<(std::ostream& os, const Value& value);
	std::ostream& operator<<(std::ostream& os, const Value* value);

	using Key = std::string;
	using TimeLimit = int;

	class IKeyValueStorage {
	public:
		virtual void				set(const Key&, const Value&, TimeLimit) = 0;
		virtual const Value*		get(const Key&) const noexcept = 0;
		virtual bool				exists(const Key&) const noexcept = 0;
		virtual bool				del(const Key&) noexcept = 0;
		virtual void				update(const Key&, const Value&) = 0;
		virtual std::vector<Key>	keys(void) const noexcept= 0;
		virtual void				rename(const Key&, const Key&) = 0;
		virtual TimeLimit			ttl(const Key&) const noexcept = 0;
		virtual std::vector<Key>	find(const Value&) const noexcept = 0;
//		virtual std::vector<Value>	showall(void) const noexcept = 0; //  согласовать использование итератора
		virtual void				upload(const std::string& filename) = 0;
//		virtual void 				export(const std::string& filename) const = 0; // delete 0
		virtual std::size_t			size() const noexcept = 0;
	};

}

#endif
