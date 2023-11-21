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

        std::string     last_name; // только буквы или -
        std::string     first_name; // только буквы или -
        std::string     birth_year;
        std::string     city; // только буквы или -
        std::string     coins_number;
    };

    bool operator==(Value, Value); // return true if one of the values is -

    using Key = std::string;
    using TimeLimit = int;

    struct Record {
        Key         key;
        Value       value;
        TimeLimit   time_limit;
    };

    class IKeyValueStorage {
    public:
        virtual void set(Key, Value, TimeLimit=-1);
        virtual Value get(Key);
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

    template<class T> // специфицировать шаблон для AbstractKeyValueStorage
    class KeyValueStorage : IKeyValueStorage {
    private:
        T _instance;
    public:
        KeyValueStorage();
        KeyValueStorage(Value&);
        KeyValueStorage(Value&&);
        KeyValueStorage& operator=(KeyValueStorage&);
        KeyValueStorage& operator=(KeyValueStorage&&);
        ~KeyValueStorage();

        void set(Key, Value, TimeLimit=-1);
        Value get(Key);
        // bool exists(Key);
        // void del(Key);
        // std::vector<Key> keys(void);
        // void rename(Key, Key);
        // TimeLimit ttl(Key);
        // std::vector<Key> find(Value);
        // std::vector<Value> showall(void);
        // void upload(const std::string& filename);
        // void s21::export(const std::string& filename);
    };

}

#endif
