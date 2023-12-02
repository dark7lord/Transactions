#ifndef S21_HASH_TABLE
#define S21_HASH_TABLE

#include "../s21_i_key_value_storage/s21_i_key_value_storage.h"
#include <list>
#include <iostream>

namespace s21 {

	typedef std::size_t HashCode;

	class HashTable : IKeyValueStorage {
	public:

		HashTable();
		HashTable(HashTable const&);
		HashTable(HashTable&&) noexcept;
		HashTable& operator=(HashTable const&);
		HashTable& operator=(HashTable&&) noexcept;
		~HashTable();

		void set(const Key&, const Value&, TimeLimit=-1) override;
		const Value* get(const Key&) const noexcept override;
		bool exists(const Key&) const noexcept override;
		bool			del(const Key&) noexcept override;
		void			update(const Key&, const Value&) override;

		std::vector<Key> keys(void) const noexcept override;
		void rename(const Key&, const Key&) override;
		TimeLimit ttl(const Key&) const noexcept override;
		std::vector<Key> find(const Value&) const noexcept override;
//		std::vector<Value> showall(void) const noexcept override; //  согласовать использование итератора
		void upload(const std::string& filename) override;
//		void s21::SelfBalancingBinarySearchTree::export(const std::string& filename) const override; // delete 0

		std::size_t size() const noexcept override;

		struct HashTableException : std::runtime_error {
			explicit HashTableException(const std::string &arg);
		};

		struct KeyException : HashTableException {
			explicit KeyException(const std::string &arg);
		};

	private:

		static constexpr std::size_t    initialBucketCount_ = 4;
		static constexpr std::size_t    maximumCapacity_ = 1 << 30;
		static constexpr double         initialLoadFactor_ = 0.75f;
		static constexpr HashCode       hashSeed_ = 4;
		static HashCode					hashCode_(const Key&) noexcept;

		struct Node {
			HashCode    hash;
			Key         key;
			Value       val;
			TimeLimit   time;
		};

		std::vector<std::list<Node>>*	table_;
		std::size_t						currentBucketCount_;
		std::size_t						currentLoadCount_;

		HashCode    		indexFor_(HashCode) const noexcept;
		double      		currentLoadFactor_() const noexcept;
		void        		increaseTable_();

		friend std::list<Node>::iterator
		first_bigger_or_equal_hash(const HashCode& hash,
								   std::list<Node>& lst) noexcept;

		friend bool
		check_key_exists(const Key& key,
						 const HashCode& hash,
						 const std::list<Node>& lst,
						 std::list<Node>::iterator first) noexcept;

	};
}

#endif
