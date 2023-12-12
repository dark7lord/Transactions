#ifndef S21_HASHTABLE
#define S21_HASHTABLE

#include <ctime>
#include <iostream>
#include <list>

#include "../../s21_i_key_value_storage/s21_i_key_value_storage.h"

namespace s21 {

typedef std::size_t HashCode;

class HashTable : public IKeyValueStorage {
 public:
  /* HashTable. Defined in HashTable_core.cpp */
  HashTable();
  HashTable(const HashTable&);
  HashTable(HashTable&&) noexcept;
  HashTable& operator=(const HashTable&);
  HashTable& operator=(HashTable&&) noexcept;
  ~HashTable();

  /* HashTable base functional. Defined in HashTable.cpp */
  void set(const Key&, const Value&, TimeLimit = -1) override;
  const Value* get(const Key&) noexcept override;
  bool exists(const Key&) noexcept override;
  bool del(const Key&) noexcept override;
  void update(const Key&, const Value&) override;
  std::vector<Key> keys() noexcept override;
  void rename(const Key&, const Key&) override;
  TimeLimit ttl(const Key&) noexcept override;
  std::vector<Key> find(const Value&) noexcept override;
  std::vector<Value> showall(void) noexcept override;
  std::size_t save(const std::string& filename) override;

 private:
  /* HashTable configurations. Defined in HashTable_core.cpp. */
  static constexpr std::size_t initial_bucket_count_ = 4;
  static constexpr std::size_t maximum_capacity_ = 1 << 30;
  static constexpr double initial_load_factor_ = 0.75f;
  static constexpr HashCode hash_seed_ = 4;
  static HashCode hashCode_(const Key&) noexcept;

  /* Key-Value pair and additional information to store in HashTable. */
  struct Node {
    HashCode hash;
    Key key;
    Value val;
    TimeLimit time_limit;
    std::time_t set_time;

    bool is_expired() noexcept;
  };

  /* HashTable private fields. Mechanism of nodes storage. Defined in
   * HashTable_core.cpp. */
  std::vector<std::list<Node>>* table_;
  std::size_t current_bucket_count_;
  std::size_t current_load_count_;

  HashCode indexFor_(HashCode) const noexcept;
  double currentLoadFactor_() const noexcept;
  void increaseTable_();

  /* Utility functions. Defined in utils.cpp. */
  std::list<Node>::iterator static first_bigger_or_equal_hash_(
      const HashCode& hash, std::list<Node>& lst) noexcept;
  bool check_key_exists_(const Key& key, const HashCode& hash,
                         std::list<Node>& lst,
                         std::list<Node>::iterator& first) noexcept;
};

}  // namespace s21

#endif  // S21_HASHTABLE
