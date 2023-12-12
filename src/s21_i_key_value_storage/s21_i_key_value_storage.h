#ifndef S21_KEY_VALUE_STORAGE
#define S21_KEY_VALUE_STORAGE

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

using Key = std::string;
using TimeLimit = int;

/* Value.cpp */
struct Value {
  std::string last_name;
  std::string first_name;
  std::string birth_year;
  std::string city;
  std::string coins_number;

  std::string& operator[](const std::string& key);
  const std::string& operator[](const std::string& key) const;

  static Value str_to_value(const std::string&, std::string* = nullptr);
  static Value parse_value(const std::string& first_name,
                           const std::string& last_name,
                           const std::string& birth_year,
                           const std::string& city,
                           const std::string& coins_number);
};

bool operator==(const Value&, const Value&);
std::ostream& operator<<(std::ostream& os, const Value& value);

/* utils.cpp */
std::string get_quoted(const std::string&);
std::vector<std::string> split_to_tokens(const std::string& line);
bool is_non_negative_integer(const std::string& s);

/* IKeyValueStorage.cpp */
class IKeyValueStorage {
 public:
  virtual void set(const Key&, const Value&, TimeLimit = -1) = 0;
  virtual const Value* get(const Key&) noexcept = 0;
  virtual bool exists(const Key&) noexcept = 0;
  virtual bool del(const Key&) noexcept = 0;
  virtual void update(const Key&, const Value&) = 0;
  virtual std::vector<Key> keys() noexcept = 0;
  virtual void rename(const Key&, const Key&) = 0;
  virtual TimeLimit ttl(const Key&) noexcept = 0;
  virtual std::vector<Key> find(const Value&) noexcept = 0;
  virtual std::vector<Value> showall() noexcept = 0;
  virtual std::size_t upload(const std::string&);
  virtual std::size_t save(const std::string&) = 0;

  virtual ~IKeyValueStorage() = default;

  static void str_to_value(const std::string& line, std::string& key,
                           Value& value);

  struct KeyValueStorageException : std::runtime_error {
    explicit KeyValueStorageException(const std::string& arg);
  };

  struct KeyExistsException : KeyValueStorageException {
    explicit KeyExistsException();
  };

  struct KeyNotExistsException : KeyValueStorageException {
    explicit KeyNotExistsException();
  };

  struct CantOpenFile : KeyValueStorageException {
    explicit CantOpenFile(const std::string& filename);
  };

  struct SyntaxError : KeyValueStorageException {
    explicit SyntaxError(const std::string& line,
                         const std::string& type_error);
  };
};

}  // namespace s21

#endif  // S21_KEY_VALUE_STORAGE
