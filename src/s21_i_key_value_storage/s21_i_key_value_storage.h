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

		std::string     last_name; // только буквы или одно -
		std::string     first_name; // только буквы или одно -
		std::string     birth_year; // только 4 цифры или одно -
		std::string     city; // только буквы или одно -
		std::string     coins_number; // любые цифры или одно -
	};

	bool operator==(Value, Value); // return true if one of the values is -

	using Key = std::string;
	using TimeLimit = int;

	class IKeyValueStorage {
	public:
		virtual void set(Key, Value, TimeLimit=-1) = 0;
		virtual const Value* get(Key) const noexcept = 0;
		// virtual bool exists(Key);
		// virtual void del(Key);
		// virtual std::vector<Key> keys(void);
		// virtual void rename(Key, Key);
		// virtual TimeLimit ttl(Key);
		// virtual std::vector<Key> find(Value);
		// virtual std::vector<Value> showall(void);
		// virtual void upload(const std::string& filename);
		// virtual void s21::export(const std::string& filename); // delete 0
	};

}

#endif
